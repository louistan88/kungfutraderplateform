import minimist from 'minimist';
import { PosDirection } from 'kungfu-shared/config/tradingConfig';
import { Observable, combineLatest } from 'rxjs';
import { filter, map } from 'rxjs/operators';
import moment from 'moment';
import { 
    transformArrayToObjectByKey, 
    makeOrderDirectionType, 
    buildTarget, 
    reqMakeOrder, 
    getAliveOrders,
    reqCancelOrder,
    calcVolumeThisStep,
    timeCheckBySecond
} from './assets/utils';
import { time } from 'console';




const argv = minimist(process.argv.slice(2), {
    string: 'ticker',
})
const { ticker, side, offset, volume, steps, triggerTime, finishTime, exchangeId, parentId, accountId } = argv;
const triggerTimeStr = moment(triggerTime).format('YYYYMMDD HH:mm:ss');
const finishTimeStr = moment(finishTime).format('YYYYMMDD HH:mm:ss');
const loopInterval = Math.ceil((finishTime - triggerTime) / steps);
const TICKER = ticker.toString().trim();
const PARENT_ID = parentId; 
    
const TARGET_DIRECTION = makeOrderDirectionType(side, offset).d;
const TARGET_DIRECTION_CONT = makeOrderDirectionType(side, offset).dc;
const OPERATION_NAME = makeOrderDirectionType(side, offset).n;
const TARGET_VOLUME = volume;
const LAST_STEP_COUNT = steps - 1;

console.log('==================== 交易信息 =======================')
console.log('[ARGS]', process.argv.slice(2).join(','))
console.log('===================================================')
console.log('[开始时间]', triggerTime, triggerTimeStr)
console.log('[结束时间]', finishTime, finishTimeStr)
console.log('[执行间隔]', loopInterval, 'ms')
console.log('[目标标的] ', TICKER)
console.log('===================================================')


//@ts-ignore
process.send({
    type: 'process:msg',
    data: {
        type: 'SUBSCRIBE_BY_TICKER',
        body: {
            ticker: TICKER,
            exchangeId,
            accountId
        }
    }
})
console.log(`[订阅] ${TICKER} ${exchangeId} ${accountId}`)

//行情request
var reqTradingDataTimer = setInterval(() => {
    //@ts-ignore
    process.send({
        type: 'process:msg',
        data: {
            type: 'REQ_LEDGER_DATA',
            body: {
                parentId: PARENT_ID,
                accountId
            }
        }
    })
}, 1000)

var secondsCounterTimer: any = null;
const TIMER_COUNT_OBSERVER = (): Observable<TimeCountData> => new Observable((subscriber) => {
    let consoledSecond: number | undefined = undefined;
    secondsCounterTimer = setInterval(() => {
        const currentTimestamp = moment().valueOf();
        
        if (currentTimestamp >= finishTime) {
            handleFinished()
            return;
        }

        const deltaMilliSeconds = currentTimestamp - triggerTime;
        const currentCount = Math.floor(deltaMilliSeconds / loopInterval)
        const currentSecond = +Number(deltaMilliSeconds / 1000).toFixed(0)

        if (currentCount <= LAST_STEP_COUNT) {
            if (consoledSecond !== currentSecond) {
                subscriber.next({
                    count: currentCount, 
                    second: currentSecond
                })
                consoledSecond = +currentSecond
            }
        }
    }, 500)
})

const PROCESS_MSG_OBSERVER = (): Observable<ProcPayload> => new Observable(subscriber => {
    process.on('message', (packet) => {
        const { type, topic, data } = packet;        
        if (type !== 'process:msg') return;
        subscriber.next({
            topic,
            data
        })
    })
})

const quotesPipe = () => {
    return PROCESS_MSG_OBSERVER().pipe(
        filter((payload: ProcPayload) => {
            return payload.topic === 'LEDGER_DATA'
        }),
        map((payload: ProcPayload): { [prop: string]: QuoteData } => {
            const { data } = payload;
            const { quotes } = data;
            const quotesAfterFilter = quotes.filter(quoteData => {
                const instrumentId = quoteData['instrumentId'];
                return TICKER === instrumentId.toString()
            })
            return transformArrayToObjectByKey(quotesAfterFilter, ['instrumentId'])
        })
    )
}

const ordersPipe = () => {
    return PROCESS_MSG_OBSERVER().pipe(
        filter((payload: ProcPayload) => {
            return payload.topic === 'LEDGER_DATA'
        }),
        map((payload: ProcPayload): OrderData[] => {
            const { data } = payload;
            const { orders } = data;
            return orders
        })
    )
}


const positionsPipe = () => {
    return PROCESS_MSG_OBSERVER().pipe(
        filter((payload: ProcPayload) => {
            return payload.topic === 'LEDGER_DATA'
        }),
        map((payload: ProcPayload): null | { [prop: string]: PosData } => {
            const { data } = payload;
            const { positions } = data;

            if (!positions || !positions.length) {
                return null
            }

            const positionsAfterFilter = positions.filter(posData => {
                const { instrumentId } = posData;
                if (TICKER === instrumentId.toString()) {
                    return true;
                }
                return false;
            })
            return transformArrayToObjectByKey(positionsAfterFilter, ['instrumentId', 'directionOrigin'])
        })
    )
}

const combineLatestObserver = combineLatest(
    TIMER_COUNT_OBSERVER(),
    quotesPipe(),
    positionsPipe(),
    ordersPipe(),
    (
        timeCountData: TimeCountData, 
        quotes: StringToQuoteData, 
        positions: StringToPosData | null, 
        orders: OrderData[]
    ) => {
        const timeTraderPipData: TimeTraderPipData = {
            timeCountData,
            quotes,
            positions,
            orders
        }

        return timeTraderPipData
    }
    
)

var dealedTimeCount: number = -1000000000;
var dealedSecond: number | undefined = undefined
var targetPosData: any = null;
var hasCancelOrderInThisLoop = false;

combineLatestObserver
.pipe(
    //============================ 时间检查 start ============================
    filter((data: TimeTraderPipData)  => {
        const { timeCountData, quotes } = data
        //记录时间发送alert
        const quote = quotes[TICKER];
        const timeCount = timeCountData.count;
        const timeSecond = timeCountData.second;
        if (timeSecond !== dealedSecond && timeSecond < 0) {
            dealedSecond = timeSecond;
            if (timeSecond < 0) {
                timeCheckBySecond(dealedSecond, quote)
            }
        }

        if (timeCount < 0) {
            return false
        }
        return true
    })
)
.pipe(
    //===================== loop之间检查，如不通过则不会进入loop start ===========
    filter((data: TimeTraderPipData) => {
        const { quotes, positions } = data
        const quote = quotes[TICKER];

        if (!quote) {
            console.error(`[WARNING] 暂无${ticker}行情信息，需保证MD进程开启`)
            return false;
        }

        if (positions === null) {
            console.error(`[WARNING] 暂无${ticker}持仓信息，需保证TD进程开启`)
            return false;
        }

        //制定全部交易计划
        const pos = positions[`${TICKER}_${TARGET_DIRECTION}`];
        if (!targetPosData) {
            const { totalVolume } = pos || {};
            targetPosData = buildTarget({ 
                offset,
                side,
                ticker,
                totalVolume: totalVolume || 0,
                targetVolume: TARGET_VOLUME
            })

            //依然没有
            if (!targetPosData) {
                return false
            };
        }
        return true;
    })
)
.pipe(
    filter((data: TimeTraderPipData) => {
        const { timeCountData} = data
        const timeCount = timeCountData.count;
        if (timeCount <= dealedTimeCount) {
            return false;
        }
        return true;
    })
)
.pipe(
    //===================== 进入loop检查，通过后才开始交易 start ================
    filter((data: TimeTraderPipData) => {
        const { timeCountData, orders } = data
        const timeCount = timeCountData.count;
        console.log(`[交易检查] ${timeCount + 1} / ${steps}, ${moment().format('HH:mm:ss')} `)
        
        // 判断是否可以交易, 如不能交易，先撤单
        const aliveOrders = getAliveOrders(orders)
        if (aliveOrders.length) {
            console.log(`[检查订单] 活动订单数量 ${aliveOrders.length} / ${orders.length}, 等待全部订单结束`)
            if (!hasCancelOrderInThisLoop) {
                reqCancelOrder(PARENT_ID)
                hasCancelOrderInThisLoop = true
                console.log(`[撤单] PARENTID: ${PARENT_ID}`)
            }
            return false
        } 
        
        return true;
    })
)
.subscribe((data: TimeTraderPipData) => {
    const { timeCountData, quotes } = data;
    const timeCount = timeCountData.count;
    const quote = quotes[TICKER];
    const positions = data.positions || {}

    //============================= 交易环节 start =============================

    //制定本次交易计划
    const instrumentType = quote.instrumentTypeOrigin;
    const unfinishedSteps = resolveUnfinishedSteps(steps - timeCount);
    const { total, thisStepVolume, currentVolume, currentVolumeCont }  = calcVolumeThisStep(
        positions,
        TICKER,
        TARGET_DIRECTION,
        TARGET_DIRECTION_CONT,
        offset,
        targetPosData,
        unfinishedSteps,
        instrumentType
    )

    if (total === 0) {
        console.log('================================================================')
        console.log(`====================== 交易任务完成 ==============================`)
        console.log('================================================================')
        handleFinished()
        return false;
    }

    //时间到，需在此处，以显示交易完成
    if (timeCount > LAST_STEP_COUNT) {
        handleFinished()
        return false;
    }

    console.log(`========= 交易条件满足，开始 ${timeCount + 1} / ${steps} =========`)

    if ((offset === 0) || (currentVolume >= thisStepVolume)) {
        console.log(`现有 ${ticker} ${PosDirection[TARGET_DIRECTION]} ${currentVolume},
        还需 ${OPERATION_NAME} ${total}, 本次需 ${OPERATION_NAME} ${thisStepVolume}`)
        if (+thisStepVolume > 0) {
            reqMakeOrder({ ...argv, volume: thisStepVolume }, quote, unfinishedSteps)    
        }
    } else {
        const deltaVolume = +Number(thisStepVolume - currentVolume).toFixed(0);
        const contOperationName = makeOrderDirectionType(side, 0).n;
        console.log(`现有 ${ticker}${PosDirection[TARGET_DIRECTION]} ${currentVolume}, ${PosDirection[TARGET_DIRECTION_CONT]} ${currentVolumeCont}
            还需 ${OPERATION_NAME} ${total}, 本次需 ${OPERATION_NAME} ${thisStepVolume}, 
            持仓不足, 需 ${OPERATION_NAME} ${currentVolume}, ${contOperationName} ${deltaVolume},
        `)

        if (+currentVolume > 0) {
            reqMakeOrder({ ...argv, volume: currentVolume }, quote, unfinishedSteps)    
        } 

        if (+deltaVolume > 0) {
            reqMakeOrder({ ...argv, offset: 0, volume: deltaVolume }, quote, unfinishedSteps)    
        }
    }

    console.log(`============ 已完成执行 ${timeCount + 1} / ${steps} ==============`)    
    hasCancelOrderInThisLoop = false;
    dealedTimeCount = timeCount; //此时记录下来
    //============================= 交易环节 end =============================
})

function resolveUnfinishedSteps (unfinishiedSteps: number) {
    //有时虽然不是最后一步，但是时间马上截止
    const currentTimestamp = moment().valueOf();
    if (finishTime - currentTimestamp < 2 * loopInterval) {
        console.log('[时间截止前，最后一步]')
        return 1
    } 
    return unfinishiedSteps
}

function handleFinished () {
    console.log(`====================== 时间截止，交易结束 ======================`)
    secondsCounterTimer && clearInterval(secondsCounterTimer)
    reqTradingDataTimer && clearInterval(reqTradingDataTimer)
    process.exit(0)
}