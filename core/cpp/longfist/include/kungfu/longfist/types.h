//
// Created by Keren Dong on 2020/1/28.
//

#ifndef KUNGFU_LONGFIST_TYPES_H
#define KUNGFU_LONGFIST_TYPES_H

#include <kungfu/common.h>
#include <kungfu/longfist/enum.h>

namespace kungfu::longfist::types {

    static constexpr int INSTRUMENT_ID_LEN = 32;
    static constexpr int PRODUCT_ID_LEN = 32;
    static constexpr int DATE_LEN = 9;
    static constexpr int EXCHANGE_ID_LEN = 16;
    static constexpr int ACCOUNT_ID_LEN = 32;
    static constexpr int CLIENT_ID_LEN = 32;
    static constexpr int SOURCE_ID_LEN = 16;
    static constexpr int BROKER_ID_LEN = 32;
    static constexpr int ERROR_MSG_LEN = 128;

    KF_DEFINE_MARK_STRUCT(PageEnd, 10000);
    KF_DEFINE_MARK_STRUCT(SessionStart, 10001);
    KF_DEFINE_MARK_STRUCT(SessionEnd, 10002);
    KF_DEFINE_MARK_STRUCT(Time, 10003);
    KF_DEFINE_MARK_STRUCT(Register, 10011);
    KF_DEFINE_MARK_STRUCT(Deregister, 10012);
    KF_DEFINE_MARK_STRUCT(RequestStart, 10025);
    KF_DEFINE_MARK_STRUCT(Location, 10026);
    KF_DEFINE_MARK_STRUCT(Subscribe, 302);
    KF_DEFINE_MARK_STRUCT(SubscribeAll, 303);
    KF_DEFINE_MARK_STRUCT(NewOrderSingle, 353);
    KF_DEFINE_MARK_STRUCT(CancelOrder, 354);
    KF_DEFINE_MARK_STRUCT(CancelAllOrder, 355);
    KF_DEFINE_MARK_STRUCT(InstrumentRequest, 356);
    KF_DEFINE_MARK_STRUCT(BrokerStateUpdate, 401);
    KF_DEFINE_MARK_STRUCT(QryAsset, 402);
    KF_DEFINE_MARK_STRUCT(InstrumentEnd, 802);
    KF_DEFINE_MARK_STRUCT(AlgoOrderInput, 210);
    KF_DEFINE_MARK_STRUCT(AlgoOrderReport, 211);
    KF_DEFINE_MARK_STRUCT(AlgoOrderModify, 212);

    KF_DEFINE_DATA_STRUCT(
            TimeRequest, 10004,
            (int32_t, id),
            (int64_t, duration),
            (int64_t, repeat)
    );

    KF_DEFINE_DATA_STRUCT(
            RequestReadFrom, 10021,
            (uint32_t, source_id),
            (int64_t, from_time)
    );

    KF_DEFINE_DATA_STRUCT(
            RequestReadFromPublic, 10022,
            (uint32_t, source_id),
            (int64_t, from_time)
    );

    KF_DEFINE_DATA_STRUCT(
            RequestWriteTo, 10023,
            (uint32_t, dest_id)
    );

    KF_DEFINE_DATA_STRUCT(
            TradingDay, 10027,
            (int64_t, timestamp)
    );

    KF_DEFINE_DATA_STRUCT(
            Channel, 10028,
            (uint32_t, source_id),
            (uint32_t, dest_id)
    );

    KF_DEFINE_DATA_STRUCT(
            Report, 10086,
            (uint32_t, source_id),
            (uint32_t, dest_id),
            (int64_t, timestamp)
    );

    KF_DEFINE_DATA_STRUCT(
            Instrument, 209,
            (CArray<char, INSTRUMENT_ID_LEN>, instrument_id),     //合约ID
            (CArray<char, EXCHANGE_ID_LEN>, exchange_id),         //交易所ID
            (InstrumentType, instrument_type),            //合约类型

            (CArray<char, PRODUCT_ID_LEN>, product_id),           //产品ID

            (int32_t, contract_multiplier),                   //合约乘数
            (double, price_tick),                         //最小变动价位

            (CArray<char, DATE_LEN>, open_date),                  //上市日
            (CArray<char, DATE_LEN>, create_date),                //创建日
            (CArray<char, DATE_LEN>, expire_date),                //到期日

            (int, delivery_year),                         //交割年份
            (int, delivery_month),                        //交割月

            (bool, is_trading),                           //当前是否交易

            (double, long_margin_ratio),                  //多头保证金率
            (double, short_margin_ratio)                 //空头保证金率
    );

    KF_DEFINE_DATA_STRUCT(
            Quote, 101,
            (CArray<char, SOURCE_ID_LEN>, source_id),              //柜台ID
            (CArray<char, DATE_LEN>, trading_day),                 //交易日

            (int64_t, data_time),                          //数据生成时间

            (CArray<char, INSTRUMENT_ID_LEN>, instrument_id),      //合约ID
            (CArray<char, EXCHANGE_ID_LEN>, exchange_id),          //交易所ID

            (InstrumentType, instrument_type),             //合约类型

            (double, pre_close_price),                     //昨收价
            (double, pre_settlement_price),                //昨结价

            (double, last_price),                          //最新价
            (int64_t, volume),                             //数量
            (double, turnover),                            //成交金额

            (double, pre_open_interest),                   //昨持仓量
            (double, open_interest),                       //持仓量

            (double, open_price),                          //今开盘
            (double, high_price),                          //最高价
            (double, low_price),                           //最低价

            (double, upper_limit_price),                   //涨停板价
            (double, lower_limit_price),                   //跌停板价

            (double, close_price),                         //收盘价
            (double, settlement_price),                    //结算价

            (CArray<double, 10>, bid_price),                       //申买价
            (CArray<double, 10>, ask_price),                       //申卖价
            (CArray<int64_t, 10>, bid_volume),                     //申买量
            (CArray<int64_t, 10>, ask_volume)                     //申卖量
    );

    KF_DEFINE_DATA_STRUCT(
            Entrust, 102,
            (CArray<char, SOURCE_ID_LEN>, source_id),              //柜台ID
            (CArray<char, DATE_LEN>, trading_day),                 //交易日

            (int64_t, data_time),                          //数据生成时间

            (CArray<char, INSTRUMENT_ID_LEN>, instrument_id),      //合约ID
            (CArray<char, EXCHANGE_ID_LEN>, exchange_id),          //交易所代码

            (InstrumentType, instrument_type),             //合约类型

            (double, price),                               //委托价格
            (int64_t, volume),                             //委托量
            (Side, side),                                  //委托方向
            (PriceType, price_type),                       //订单价格类型（市价、限价、本方最优）

            (int64_t, main_seq),                           //主序号
            (int64_t, seq)                                //子序号
    );

    KF_DEFINE_DATA_STRUCT(
            Transaction, 103,
            (CArray<char, SOURCE_ID_LEN>, source_id),              //柜台ID
            (CArray<char, DATE_LEN>, trading_day),                 //交易日

            (int64_t, data_time),                          //数据生成时间

            (CArray<char, INSTRUMENT_ID_LEN>, instrument_id),      //合约ID
            (CArray<char, EXCHANGE_ID_LEN>, exchange_id),          //交易所代码

            (InstrumentType, instrument_type),             //合约类型

            (double, price),                               //成交价
            (int64_t, volume),                             //成交量

            (int64_t, bid_no),                             //买方订单号
            (int64_t, ask_no),                             //卖方订单号

            (ExecType, exec_type),                         //SZ: 成交标识
            (BsFlag, bs_flag),                            //SH: 内外盘标识

            (int64_t, main_seq),                               //主序号
            (int64_t, seq)                                    //子序号
    );

    KF_DEFINE_DATA_STRUCT(
            Bar, 110,
            (CArray<char, DATE_LEN>, trading_day),            //交易日
            (CArray<char, INSTRUMENT_ID_LEN>, instrument_id), //合约代码
            (CArray<char, EXCHANGE_ID_LEN>, exchange_id),     //交易所代码

            (int64_t, start_time),                    //开始时间
            (int64_t, end_time),                      //结束时间

            (double, open),                           //开
            (double, close),                          //收
            (double, low),                            //低
            (double, high),                           //高

            (int64_t, volume),                        //区间交易量
            (int64_t, start_volume),                  //初始总交易量

            (int32_t, tick_count)                    //区间有效tick数
    );

    KF_DEFINE_DATA_STRUCT(
            OrderInput, 201,
            (uint64_t, order_id),                       //订单ID

            (CArray<char, INSTRUMENT_ID_LEN>, instrument_id),   //合约代码
            (CArray<char, EXCHANGE_ID_LEN>, exchange_id),       //交易所代码

            (CArray<char, SOURCE_ID_LEN>, source_id),           //柜台ID
            (CArray<char, ACCOUNT_ID_LEN>, account_id),         //账号ID

            (InstrumentType, instrument_type),          //合约类型

            (double, limit_price),                      //价格
            (double, frozen_price),                     //冻结价格

            (int64_t, volume),                          //数量

            (Side, side),                               //买卖方向
            (Offset, offset),                           //开平方向
            (HedgeFlag, hedge_flag),                    //投机套保标识
            (PriceType, price_type),                    //价格类型
            (VolumeCondition, volume_condition),        //成交量类型
            (TimeCondition, time_condition),            //成交时间类型

            (uint64_t, parent_id)                      //母订单ID
    );

    KF_DEFINE_DATA_STRUCT(
            OrderAction, 202,
            (uint64_t, order_id),                       //订单ID
            (uint64_t, order_action_id),                //订单操作ID

            (OrderActionFlag, action_flag),             //订单操作类型

            (double, price),                            //价格
            (int64_t, volume)                          //数量
    );

    KF_DEFINE_DATA_STRUCT(
            OrderActionError, 202,
            (uint64_t, order_id),                       //订单ID
            (uint64_t, order_action_id),                //订单操作ID
            (int32_t, error_id),                        //错误ID
            (CArray<char, ERROR_MSG_LEN>, error_msg)           //错误信息
    );

    KF_DEFINE_DATA_STRUCT(
            Order, 203,
            (uint64_t, parent_id),                      //母订单ID
            (uint64_t, order_id),                       //订单ID

            (int64_t, insert_time),                     //订单写入时间
            (int64_t, update_time),                     //订单更新时间

            (CArray<char, DATE_LEN>, trading_day),              //交易日

            (CArray<char, INSTRUMENT_ID_LEN>, instrument_id),   //合约ID
            (CArray<char, EXCHANGE_ID_LEN>, exchange_id),       //交易所ID

            (CArray<char, SOURCE_ID_LEN>, source_id),           //柜台ID
            (CArray<char, ACCOUNT_ID_LEN>, account_id),         //账号ID
            (CArray<char, CLIENT_ID_LEN>, client_id),           //Client ID

            (InstrumentType, instrument_type),          //合约类型

            (double, limit_price),                      //价格
            (double, frozen_price),                     //冻结价格，市价单冻结价格为0

            (int64_t, volume),                          //数量
            (int64_t, volume_traded),                   //成交数量
            (int64_t, volume_left),                     //剩余数量

            (double, tax),                              //税
            (double, commission),                       //手续费

            (OrderStatus, status),                      //订单状态

            (int32_t, error_id),                        //错误ID
            (CArray<char, ERROR_MSG_LEN>, error_msg),           //错误信息

            (Side, side),                               //买卖方向
            (Offset, offset),                           //开平方向
            (HedgeFlag, hedge_flag),                    //投机套保标识
            (PriceType, price_type),                    //价格类型
            (VolumeCondition, volume_condition),        //成交量类型
            (TimeCondition, time_condition)            //成交时间类型
    );

    KF_DEFINE_DATA_STRUCT(
            Trade, 204,
            (uint64_t, trade_id),                       //成交ID

            (uint64_t, order_id),                       //订单ID
            (uint64_t, parent_order_id),                //母订单ID

            (int64_t, trade_time),                     //成交时间
            (CArray<char, DATE_LEN>, trading_day),              //交易日

            (CArray<char, INSTRUMENT_ID_LEN>, instrument_id),   //合约ID
            (CArray<char, EXCHANGE_ID_LEN>, exchange_id),       //交易所ID
            (CArray<char, SOURCE_ID_LEN>, source_id),           //柜台ID
            (CArray<char, ACCOUNT_ID_LEN>, account_id),         //账号ID
            (CArray<char, CLIENT_ID_LEN>, client_id),           //Client ID

            (InstrumentType, instrument_type),          //合约类型

            (Side, side),                               //买卖方向
            (Offset, offset),                           //开平方向
            (HedgeFlag, hedge_flag),                    //投机套保标识

            (double, price),                            //成交价格
            (int64_t, volume),                          //成交量
            (int64_t, close_today_volume),              //平今日仓量(期货)

            (double, tax),                              //税
            (double, commission)                       //手续费
    );

    KF_DEFINE_DATA_STRUCT(
            Position, 205,
            (int64_t, update_time),                     //更新时间
            (CArray<char, DATE_LEN>, trading_day),              //交易日

            (CArray<char, INSTRUMENT_ID_LEN>, instrument_id),   //合约ID
            (InstrumentType, instrument_type),          //合约类型
            (CArray<char, EXCHANGE_ID_LEN>, exchange_id),       //交易所ID

            (uint32_t, holder_uid),
            (LedgerCategory, ledger_category),

            (CArray<char, SOURCE_ID_LEN>, source_id),           //柜台ID
            (CArray<char, ACCOUNT_ID_LEN>, account_id),         //账号ID
            (CArray<char, CLIENT_ID_LEN>, client_id),           //Client ID

            (Direction, direction),                     //持仓方向

            (int64_t, volume),                          //数量
            (int64_t, yesterday_volume),                //昨仓数量
            (int64_t, frozen_total),                    //冻结数量
            (int64_t, frozen_yesterday),                //冻结昨仓

            (double, last_price),                       //最新价

            (double, avg_open_price),                   //开仓均价
            (double, position_cost_price),              //持仓成本价

            (double, close_price),                      //收盘价(股票和债券)
            (double, pre_close_price),                  //昨收价(股票和债券)

            (double, settlement_price),                 //结算价(期货)
            (double, pre_settlement_price),             //昨结算(期货)

            (double, margin),                           //保证金(期货)
            (double, position_pnl),                     //持仓盈亏(期货)
            (double, close_pnl),                        //平仓盈亏(期货)

            (double, realized_pnl),                     //已实现盈亏
            (double, unrealized_pnl)                   //未实现盈亏
    );

    KF_DEFINE_DATA_STRUCT(
            PositionEnd, 800,
            (uint32_t, holder_uid)
    );

    KF_DEFINE_DATA_STRUCT(
            Asset, 206,
            (int64_t, update_time),               //更新时间
            (CArray<char, DATE_LEN>, trading_day),        //交易日

            (uint32_t, holder_uid),
            (LedgerCategory, ledger_category),

            (CArray<char, SOURCE_ID_LEN>, source_id),     //柜台ID
            (CArray<char, BROKER_ID_LEN>, broker_id),     //Broker ID
            (CArray<char, ACCOUNT_ID_LEN>, account_id),   //账号ID
            (CArray<char, CLIENT_ID_LEN>, client_id),     //client ID

            (double, initial_equity),             //期初权益
            (double, static_equity),              //静态权益
            (double, dynamic_equity),             //动态权益

            (double, realized_pnl),               //累计收益
            (double, unrealized_pnl),

            (double, avail),                      //可用资金
            (double, market_value),               //市值(股票)

            (double, margin),                     //保证金(期货)

            (double, accumulated_fee),            //累计手续费
            (double, intraday_fee),               //当日手续费

            (double, frozen_cash),                //冻结资金(股票: 买入挂单资金), 期货: 冻结保证金+冻结手续费)
            (double, frozen_margin),              //冻结保证金(期货)
            (double, frozen_fee),                 //冻结手续费(期货)

            (double, position_pnl),               //持仓盈亏(期货)
            (double, close_pnl)                  //平仓盈亏(期货)
    );

    KF_DEFINE_DATA_STRUCT(
            PositionDetail, 208,
            (int64_t, update_time),                     //更新时间
            (CArray<char, DATE_LEN>, trading_day),              //交易日

            (CArray<char, INSTRUMENT_ID_LEN>, instrument_id),   //合约ID
            (InstrumentType, instrument_type),          //合约类型
            (CArray<char, EXCHANGE_ID_LEN>, exchange_id),       //交易所ID

            (uint32_t, holder_uid),

            (CArray<char, SOURCE_ID_LEN>, source_id),           //柜台ID
            (CArray<char, ACCOUNT_ID_LEN>, account_id),         //账号ID
            (CArray<char, CLIENT_ID_LEN>, client_id),           //Client ID

            (Direction, direction),                     //持仓方向

            (int64_t, volume),                          //数量
            (int64_t, frozen_volume),                   //冻结数量

            (double, last_price),                       //最新价
            (double, open_price),                       //开仓价

            (double, settlement_price),                 //结算价(期货)
            (double, pre_settlement_price),             //昨结算(期货)

            (CArray<char, DATE_LEN>, open_date),                //开仓日(YYYYMMDD,仅期货明细和债券)

            (uint64_t, trade_id),                       //成交ID
            (int64_t, trade_time)                      //成交时间
    );

    KF_DEFINE_DATA_STRUCT(
            PositionDetailEnd, 801,
            (uint32_t, holder_uid)
    );

    KF_DEFINE_DATA_STRUCT(
            InstrumentCommissionRate, 214,
            (CArray<char, INSTRUMENT_ID_LEN>, instrument_id), //合约代码
            (CArray<char, EXCHANGE_ID_LEN>, exchange_id),     //交易所代码


            (InstrumentType, instrument_type),         //合约类型

            (CArray<char, ACCOUNT_ID_LEN>, account_id),        //账户ID
            (CArray<char, BROKER_ID_LEN>, broker_id),          //Broker ID

            (CommissionRateMode, mode),                //手续费模式(按照交易额或者交易量)

            (double, open_ratio),                      //开仓费率
            (double, close_ratio),                     //平仓费率
            (double, close_today_ratio),               //平今费率

            (double, min_commission)                  //最小手续费
    );

    inline void order_from_input(const OrderInput &input, Order &order) {
        order.parent_id = input.parent_id;
        order.order_id = input.order_id;
        strcpy(order.instrument_id, input.instrument_id);
        strcpy(order.exchange_id, input.exchange_id);
        strcpy(order.source_id, input.source_id);
        strcpy(order.account_id, input.account_id);

        order.limit_price = input.limit_price;
        order.frozen_price = input.frozen_price;

        order.volume = input.volume;
        order.volume_traded = 0;
        order.volume_left = input.volume;
        order.status = OrderStatus::Submitted;

        order.side = input.side;
        order.offset = input.offset;
        order.hedge_flag = input.hedge_flag;

        order.price_type = input.price_type;
        order.volume_condition = input.volume_condition;
        order.time_condition = input.time_condition;
    }
}

#endif //KUNGFU_LONGFIST_TYPES_H
