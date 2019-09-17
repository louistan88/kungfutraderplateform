import strategy from '@/components/strategy/index'
import account from '@/components/account/index'
import monitor from '@/components/monitor/index';
import { getAccountsStrategys, accountStrategyListStringify } from '@/assets/scripts/actions';
const inquirer = require('inquirer');
inquirer.registerPrompt('autocomplete', require('inquirer-autocomplete-prompt'));

export const monitPrompt = async (list: boolean) => {  
    if(!list) return monitor();
    
    const { accounts, strategys } = await getAccountsStrategys();
    const accountStrategyList = accountStrategyListStringify(accounts, strategys);
    let answers = await inquirer.prompt([
        {
            type: 'autocomplete',
            name: 'processName',
            message: 'Select target account / strategy process to monit    ',
            source: async (answersSoFar: any, input = '') => {
                return accountStrategyList
                    .filter((s: string) => s.indexOf(input) !== -1)
            }
        }
    ]);

    //it is so damn important, because inquirer event will conflict with blessed
    process.stdin.removeAllListeners('data'); 

    const { processName } = answers;
    const processSplit = processName.split(' ')
    const processId = processSplit[processSplit.length - 1].trim();
    const type = processSplit[0].indexOf('strategy') !== -1 ? 'strategy' : 'account';
    if (type === 'account') {
        return account(processId)
    } else if(type === 'strategy') {
        return strategy(processId)
    }
}