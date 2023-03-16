export default {
  keyword_input: 'keyword',
  empty_text: 'no data',
  success: 'success',
  error: 'error',
  add: 'Add',
  close: 'Close',
  delete: 'delete',
  rename: 'rename',
  set: 'Set',
  clean: 'clean',
  help: 'Help',
  run: 'Run',
  quit: 'Quit',
  operation_success: 'operation success',
  operation_failed: 'operation failed',
  location_error: 'current location error',
  watcher_error: 'Watcher is NULL',
  instrument_error: 'instrument error',
  component_error: 'component error',
  board_empty: 'Not added any board',
  add_board_now: 'Add now',
  prompt: 'prompt',
  warning: 'warning',
  confirm: 'confirm',
  cancel: 'cancel',
  save_file: 'save file',
  detail: 'detail',
  ok: 'ok',
  yes: 'yes',
  no: 'no',

  edit: 'Edit',
  copy: 'Copy',
  paste: 'Paste',
  select_all: 'Select all',
  undo: 'Undo',

  open_resources_directory: 'Open Kungfu Resources directory (KF_HOME)',
  open_install_directory: 'Open Kungfu installation directory',
  open_basic_configuration: 'Open Kungfu basic configuration DB',
  browsing_log: 'Browsing log files',

  clear_journal: 'Clear journal',
  clear_DB: 'Clear DB',
  reset_main_panel: 'Reset main panel',
  export_all_transaction_data: 'Export all transaction data',

  website: 'Website',
  user_manual: 'User manual',
  API_documentation: 'Strategy API documentation',
  Kungfu_forum: 'Kungfu forum',

  KungFu: 'Kungfu',
  about_kungfu: 'About Kungfu',

  file: 'File',
  folder: 'Folder',

  no_focus: 'The current page is not in focus',
  clear: 'Clearing {content} completed, please restart the application',
  open_window: 'Opening window',
  open_code_editor: 'Opening code editor',
  open_trading_task_view: 'Opening trading task view',
  add_board: 'Add Board',
  select_board: 'Please select the board to add',
  add_board_error: 'Add board target error',
  select_date: 'Select Date',
  date_type: 'Date Type',
  natural_day: 'Natural Day',
  trading_day: 'Trading Day',

  delete_category:
    'Delete all data in {category}, if the {categoryName} process is running, the process will also be stopped, confirm deletion',
  add_config_modal:
    '{category} ID unique in the system. {changeTypeName} cannot be modified after it succeeds.',
  update_config_modal: 'Confirm {key} configurations',
  database_locked: 'The database is occupied now, please wait and retry.',

  MakeOrder: 'Order Dashboard',
  FutureArbitrage: 'Future Arbitrage',
  BlockTrade: 'Block Trade',
  OrderBook: 'Order Book',
  MarketData: 'Market Data',
  TradingTask: 'Trading Task',
  Strategy: 'Strategy',
  Md: 'Md',
  Td: 'Td',
  Trade: 'Trade',
  Order: 'Order',
  PosGlobal: 'Positon Global',
  Pos: 'Positon',

  please_wait: '请稍后',

  baseConfig: {
    main_panel: 'HOME',
    control_center: 'Control',
  },

  settingsFormConfig: {
    keyword: 'Keyword',
    add_csv: 'Import Csv',
    csv_template: 'Download Csv Template',
    add_csv_desc: 'csv headers are {header}',
    clear: 'Clear',
    total: 'Total {sum} pieces of data',
  },

  tradingConfig: {
    unknown: 'Unknown',
    quantity: 'Quantity',
    proportion: 'Proportion',
    default: 'Default',
    order_task: 'Trade',

    running: 'Running',
    stopping: 'Stopping',
    stopped: 'Stopped',
    launching: 'Launching',
    error: 'Errored',
    waiting_restart: 'Stopped',

    pending: 'Pending',
    Idle: 'Idle',
    dis_connected: 'Disconnected',
    connected: 'Connected',
    logged_in: 'LoggedIn',
    login_failed: 'LoginFailed',
    ready: 'Ready',

    system: 'System',
    daemon: 'Daemon',
    md: 'Md',
    td: 'Td',
    strategy: 'Strategy',

    open: 'Open',
    close: 'Close',
    close_today: 'CloseToday',
    close_yesterday: 'CloseYest',

    by_quantity: 'ByQuantity',
    by_proportion: 'ByProportion',

    latest: 'Latest Price',
    sell5: 'Fifth Sell Price',
    sell4: 'Fourth Sell Price',
    sell3: 'Third Sell Price',
    sell2: 'Second Sell Price',
    sell1: 'First Sell Price',
    buy1: 'First Buy Price',
    buy2: 'Second Buy Price',
    buy3: 'Third Buy Price',
    buy4: 'Fourth Buy Price',
    buy5: 'Fifth Buy Price',
    up_limit_price: 'High Limit Price',
    low_limit_price: 'Low Limit Price',

    buy: 'Buy',
    sell: 'Sell',
    lock: 'Lock',
    unlock: 'Unlock',
    exec: 'Exec',
    drop: 'Drop',
    purchase: 'Purchase',
    redemption: 'Redemption',
    split: 'Split',
    merge: 'Merge',
    margin_trade: 'MarginTrade',
    short_sell: 'ShortSell',
    repay_margin: 'RepayMargin',
    repay_short: 'RepayShort',
    cash_repay_margin: 'CashRepayMargin',
    stock_repay_short: 'StockRepayShort',
    surplus_stock_transfer: 'SurplusStockTransfer',
    guarantee_stock_transfer: 'GuaranteeStockTransferIn',
    guarantee_stock_redeem: 'GuaranteeStockTransferOut',

    submitted: 'Submitted',
    cancelled: 'Cancelled',
    filled: 'Filled',
    partial_filled_not_active: 'PartialFilledNotActive',
    partial_filled_active: 'PartialFilledActive',
    lost: 'Lost',

    long: 'Long',
    short: 'Short',

    Limit: 'Limit',
    Market: 'Market',
    FakBest5: 'FakBest5',
    Forward_best: 'ForwardBest',
    Reverse_best: 'ReverseBest',
    Fak: 'Fak',
    Fok: 'Fok',

    speculation: 'Speculation',
    hedge: 'Hedge',
    arbitrage: 'Arbitrage',
    covered: 'Covered',

    any: 'Any',
    min: 'Min',
    all: 'All',

    by_amount: 'ByAmount',
    by_volume: 'ByVolume',

    IOC: 'IOC',
    GFD: 'GFD',
    GTC: 'GTC',

    stock: 'Stock',
    future: 'Future',
    bond: 'Bond',
    stock_option: 'StockOption',
    fund: 'Fund',
    tech_stock: 'TechStock',
    index: 'Index',
    repo: 'Repo',
    warrant: 'Warrant',
    iopt: 'Iopt',
    crypto: 'Crypto',
    crypto_future: 'CryptoFuture',
    multi: 'Multi',

    SSE: 'SSE',
    SZE: 'SZE',
    BSE: 'BSE',
    SHFE: 'SHFE',
    DCE: 'DCE',
    CZCE: 'CZCE',
    CFFEX: 'CFFEX',
    INE: 'INE',

    HK: 'HK',
    HKFUT: 'HKFUT',
    US: 'US',
    USFUT: 'USFUT',
    SGX: 'SGX',
    SGXFUT: 'SGXFUT',
    EUR: 'EUR',
    EURFUT: 'EURFUT',
    LON: 'LON',
    LONFUT: 'LONFUT',
    AEX: 'AEX',
    AEXFUT: 'AEXFUT',
    AUX: 'AUX',
    AUXFUT: 'AUXFUT',
    HEXS: 'HEXS',
    HEXSFUT: 'HEXSFUT',
    IDX: 'IDX',
    IDXFUT: 'IDXFUT',
    KORC: 'KORC',
    LME: 'LME',
    MYS: 'MYS',
    MYSFUT: 'MYSFUT',
    ABB: 'ABB',
    PRX: 'PRX',
    PRXFUT: 'PRXFUT',
    SIX: 'SIX',
    SIXFUT: 'SIXFUT',
    TAX: 'TAX',
    TAXFUT: 'TAXFUT',
    JP: 'JP',
    JPFUT: 'JPFUT',
    TSE: 'TSE',
    TSEFUT: 'TSEFUT',
    XETRA: 'XETRA',
    GLFX: 'GLFX',
    IPE: 'IPE',
    CBOT: 'CBOT',
    CEC: 'CEC',
    LIFE: 'LIFE',
    MTIF: 'MTIF',
    NYCE: 'NYCE',
    CMX: 'CMX',
    NYME: 'NYME',
    SIME: 'SIME',
    CME: 'CME',
    IMM: 'IMM',
    WIDX: 'WIDX',
    FREX: 'FREX',
    METL: 'METL',
    IPM: 'IPM',

    SP: 'SP',
    SPC: 'SPC',
    SPD: 'SPD',
    IPS: 'IPS',

    CNY: 'CNY',
    HKD: 'HKD',
    USD: 'USD',
    JPY: 'JPY',
    GBP: 'GBP',
    EURO: 'EUR',
    CNH: 'CNH',
    SGD: 'SGD',
    MYR: 'MYR',

    master: 'master',
    ledger: 'ledger',
    cached: 'cached',
    archive: 'archive',

    place_order: 'Place Order',
    apart_order: 'Apart Order',
    reset_order: 'Reset',
    account: 'AccountId',
    instrument: 'Instrument',
    instrument_type: 'Instrument Type',
    volume: 'Volume',
    price: 'Price',
    protect_price: 'Protect Price',
    price_type: 'Price Type',
    price_level: 'Price Level',
    price_offset: 'Price Offset',
    side: 'Side',
    offset: 'Offset',
    direction: 'Direction',
    limit_price: 'LimitPrice',
    algorithm: 'Algorithm',

    make_order_number: 'Order Number',
    no_empty: 'Order quantity cannot be empty',
    total_order_amount: 'Total Order Amount',
    every_volume: 'Every Volume',

    fat_finger_buy_modal:
      'The buying price exceeded the warning line, the current price is {price}, line for {warningLine}, fat finger is {fatFinger}%',
    fat_finger_sell_modal:
      'The selling price exceeded the warning line, the current price is {price}, line for {warningLine}, fat finger is {fatFinger}%',
    close_apart_open_modal:
      'The order input volume is {volume}, the current closable {direction} position is {closable_volume}, the excess is {open_volume}\nclick “Take excess to open”, will close {direction} {closable_volume}, open {direction} {open_volume}\nclick “Orignal plan”, will continue close {direction} {volume}',
    start_process: 'please start {process} first',
    place_confirm: 'Place Order Confirm',
    continue_close_rate:
      'Exceed the close warning value ({rate}%), if you want to continue to make order?',
    Continue: 'Continue',
    original_plan: 'Orignal plan',
    beyond_to_open: 'Take excess to open',
  },

  orderConfig: {
    update_time: 'update_time',
    instrument_id: 'instrument_id',
    limit_price: 'limit_price',
    order_status: 'order_status',
    latency_system: 'latency_system(μs)',
    latency_network: 'latency_network(μs)',
    avg_price: 'avg_price',
    dest_uname: 'dest_uname',
    source_uname: 'source_uname',
    completed: 'completed',
    clinch: 'clinch',
    all: 'all',

    mean: 'mean',
    max: 'max',
    min: 'min',
    volume: 'volume',

    checkbox_text: 'Outstanding delegate',
    cancel_all: 'All cancellations',
    date_picker: 'Select a date',
    confirm_cancel_all: 'Confirm cancellation of all orders',
    entrust: 'Entrust',
    start: 'Please Start',
    td: 'TD',
    confirm: 'confirm',

    entrust_statistical: 'Entrust Statistical',
    statistical_desc: 'Real-time (latest {count} pieces of data)',
    entrust_statistical_number: 'Entrust Statistical Number',
    entrust_statistical_price: 'Entrust Statistical Price',
    average_withdrawal_ratio:
      'Average withdrawal ratio (only partial withdrawal and total withdrawal of statistics Department)',
    average_system_latency: 'Average System Latency(μs)',
    min_system_latency: 'Min System Latency(μs)',
    max_system_latency: 'Max System Latency(μs)',
    average_network_latency: 'Average Network Latency(μs)',
    min_network_latency: 'Min Network Latency(μs)',
    max_network_latency: 'Max Network Latency(μs)',
  },

  tdConfig: {
    td_group: 'Td Group',
    td_name: 'Td Group Name',
    account_name: 'account',
    account_ps: 'note',
    state_status: 'status',
    process_status: 'process',
    unrealized_pnl: 'unrealized_pnl',
    marked_value: 'marked_value',
    margin: 'margin',
    avail_money: 'avail_money',
    avail_margin: 'avail_margin',
    cash_debt: 'cash_debt',
    total_asset: 'total_asset',
    actions: 'actions',

    add_td: 'Add',
    add_group_placeholder: 'Add group',
    set_td_group: 'Account Group Settings',
    account_group: 'Account Group',
    td_not_found: '{td} Td not found',
    sourse_not_found:
      'The configuration item does not exist, please check {value} package.json',
    need_only_group: 'Ensure that the account group name is unique',
    delete_amount_group: 'Deleting account Group {group}',
    confirm_delete_group:
      'The account process under account group change will not be affected, confirm the deletion',
  },

  mdConfig: {
    counter_name: 'counter_name',
    state_status: 'status',
    process_status: 'process',
    actions: 'actions',
    select_counter_api: 'Select a counter',
    select_trade_task: 'Select trade task',
    select_plugin_type: 'Select plugin type',

    add_md: 'Add',
    counter_plugin_inexistence: 'Counter plugin inexistence',
  },

  strategyConfig: {
    strategy: 'strategy',
    strategy_id: 'strategy_id',
    strategy_file: 'strategy_file',
    strategy_path: 'strategy_path',
    strategy_path_tip:
      'Normal python strategy use .py file, packaged strategy use .so or .pyd file in strategy folder',
    process_status: 'process',
    unrealized_pnl: 'unrealized_pnl',
    marked_value: 'marked_value',
    actions: 'actions',
    strategy_tip: 'Ensure that the strategy_id is unique',

    add_strategy: 'Add',
  },

  tradingTaskConfig: {
    task_id: 'task_id',
    process_status: 'process',
    args: 'arguments',
    actions: 'actions',

    add_task: 'Add',
    illegal_process_id: 'Not a legitimate trade task process_id',
    key_inexistence: 'The trade task plugin key does not exist',
    plugin_inexistence: 'The trade task plugin does not exist',
    configuration_inexistence:
      'The configuration item does not exist,please check',
    delete_task: 'Deleting a trade Task',
    delete_task_content:
      'all data, if the transaction task is running, will also stop the process and confirm deletion',
  },

  posGlobalConfig: {
    instrument_id: 'instrument_id',
    account_id_resolved: 'account_id_resolved',
    yesterday_volume: 'yesterday_volume',
    today_volume: 'today_volume',
    sum_volume: 'sum_volume',
    frozen_total: 'frozen_total',
    frozen_volume: 'frozen',
    closable_volume: 'closable',
    avg_open_price: 'avg_price',
    last_price: 'last_price',
    unrealized_pnl: 'unrealized_pnl',
  },

  marketDataConfig: {
    instrument_id: 'instrument_id',
    open_price: 'open_price',
    high_price: 'high_price',
    low_price: 'low_price',
    last_price: 'last_price',
    volume: 'volume',
    actions: 'actions',

    subscribe_btn: 'Subscribe',
    add_market: 'Add',
  },

  tradeConfig: {
    trade_time_resolved: 'trade_time',
    kf_time_resolved: 'kf_time',
    instrument_id: 'instrument_id',
    price: 'price',
    volume: 'volume',
    latency_trade: 'latency_trade(μs)',

    mean_price: 'Mean Price',
    min_price: 'Min Price',
    max_price: 'Max Price',

    statistical: 'Transaction Statistical',
    statistical_count: 'Statistics of transaction quantity',
    statistical_price: 'Transaction price statistics',
    statistical_desc: 'Real-time (latest 500 pieces of data)',
    average_trade_latency: 'Average transaction delay(μs)',
    max_trade_latency: 'Max transaction delay(μs)',
    min_trade_latency: 'Min transaction delay(μs)',

    greater_than_limit_value:
      'The order propety {key}`s maximum for current instrument is {value}',
  },

  futureArbitrageConfig: {
    account_name: 'account_name',
    future_arbitrage_code: 'future_arbitrage_code',
    instrument_buy_A: 'instrument_buy_A',
    instrument_sell_A: 'instrument_sell_A',
    instrument_buy_B: 'instrument_buy_B',
    instrument_sell_B: 'instrument_sell_B',
    side: 'side',
    offset: 'offset',
    hedge_flag: 'hedge_flag',
    is_swap: 'is_swap',
    price_type: 'price_type',
    limit_price: 'limit_price A-B',
    volume: 'volume',

    place_order: 'Place Order',
    reset_order: 'Reset',
    only_corresponding: 'Can Only corresponding',
  },

  blockTradeConfig: {
    account_name: 'account_name',
    instrument_id: 'instrument',
    side: 'side',
    offset: 'offset',
    hedge_flag: 'hedge_flag',
    is_swap: 'is_swap',
    price_type: 'price_type',
    limit_price: 'limit_price',
    volume: 'volume',
    opponent_seat: 'opponent_seat',
    match_number: 'match_number',
    is_specific: 'is_specific',

    unrestricted_shares: 'Unrestricted shares',
    restricted_shares: 'Restricted shares',

    place_order: 'Place Order',
    reset_order: 'Resert',
    only_number: 'can only number',
  },

  globalSettingConfig: {
    global_setting_title: 'Global Setting',
    system: 'System',
    log_level: 'Log Level',
    for_all_log: 'For all Log',

    auto_restart_td: 'Trading Process Auto Restart',
    auto_restart_td_desc:
      'While the trade process interruption, if this switch open, it will try to reconnect three times; if closed, it will not. During the restart process (from restart to trade process ready) , the position queried in the strategy will be 0, both `on_deregister` and `on_broker_state_change` methods need to be used within the policy to determine whether the status of the counter is `disconnected` or `restart ready`.',

    language: 'Language',
    select_language_desc: 'Select Language, the modified restart takes effect',
    bypass_archive: 'ByPass Archive',
    bypass_archive_desc:
      'Archive only delete journal and logs, zip nomore files',

    porformance: 'Performance',
    rocket_model: 'Open Rocket Model',
    rocket_model_desc:
      'Use CPU 100% (only when the CPU is greater than 4 core can open it) , restart is required',
    bypass_accounting: 'Bypass UI Accounting',
    bypass_accounting_desc:
      'UI process no longer dealing with calculation, restart is required',
    bypass_trading_data: 'Pure Monitor Mode',
    bypass_trading_data_desc:
      'Only monit processes status, ui costs lowest, restart is required',
    strategy: 'Strategy',
    use_local_python: 'Use Local Python',
    local_python_desc:
      'Pip3 install *.whl in {whl_dir_path}, local python version require {py_version}',
    python_path: 'Select Local Python Path',
    python_path_desc:
      'local python path is required to be selected, and kungfu*.whl should be installed in this path',

    currency: 'Currency',
    instrument_currency: 'Instrument Currency',
    instrument_currency_desc:
      'If open, will show the instrument currency type after instrument name in Position board',

    trade: 'Trade',
    sound: 'Traded Sound',
    use_sound: 'Enable the system traded prompt sound',
    fat_finger_threshold: 'Fat Finger Threshold',
    set_fat_finger:
      'Set the threshold for triggering an fat finger(percentage)',
    close_threshold: 'Close Threshold',
    set_close_threshold:
      'Set the threshold for triggering an close(percentage)',
    trade_limit: 'Trade Limit',
    set_trade_limit: 'Set Trade limit value for price or volume property',
    order_input_key: 'Property',
    single_price: 'Single Price',
    limit_value: 'Maximum',
    asset_margin: 'AssetMargin',
    show_asset_margin: 'AssetMargin Mode',

    code_editor: 'Editor',
    tab_space_type: 'Indentation Category',
    set_tab_space: 'Kungfu Editor Indentation Category',
    tab_space_size: 'Indentation Size',
    set_tab_space_size: 'Kungfu Editor Indentation Size (space)',

    comission: 'Comission',
    varieties: 'Varieties',
    add_comission: 'Add',
    exchange_id: 'Exchange ID',
    open: 'Open',
    close_today: 'Close Today',
    close_yesterday: 'Close Yesterday',
    min: 'Min',

    update: 'Upgrade Version',
    is_check_version: 'Check Version',
    is_check_version_desc: 'Check the client version when start kungfu',
    current_version: 'Current version',
    already_latest_version: 'Already latest version',
    new_version: 'New version',
    start_download: 'Start Download',
    find_new_version: 'Found new version: {version}\nIf you want download now?',
    downloaded: 'Download finished, wait to install',
    to_install: 'To install',
    warning_before_install:
      "Installing will clean today's trading data and quit Kungfu (If you need, make a backup at first), sure install now? (suggest install when today's trade end)",
  },

  风控: 'Risk Setting',
  风控描述:
    'Enable risk setting to automatically close positions when positions exceed thresholds',
  账户: 'Account',
  柜台: 'Exchange',
  单比最大量: 'Maximum single ratio',
  每日最大成交量: 'Maximum daily turnover',
  防止自成交: 'Whether automatic success detection is required',
  最大回撤率: 'Maximum withdrawal rate',
  标的白名单: 'white list',
  白名单设置警告: 'Please set the whitelist for this account first',

  validate: {
    no_special_characters: 'Cannot contain special characters',
    no_underscore: 'Cannot contain underscores',
    no_zero_number: 'Cannot contain zero',
    no_negative_number: 'Cannot contain negative',
    value_existing: '{value} has been in existence',
    mandatory: 'mandatory',
    resolved_tip: 'Success resolved {success} {value}, failed {fail}',
  },

  editor: {
    set_strategy_entrance: 'Set Strategy Entry',
    current_strategy: 'Current strategy',
    new_file: 'New File',
    new_folder: 'New Folder',
    set_strategy_success: 'Strategy {file} file path changed successfully',
    entry_file: 'Entry File',
    creaate_success: '{file} created successfully',

    name_repeat:
      'This location already exists file or folder {name}, please select a different name',
    empty_input: 'File or folder name must be provided',
    illegal_character: 'The name cannot contain \\/:*?" <>|',
    delate_confirm: 'Are you sure to delete {value}?',
    cannot_delate_entry: 'Cannot delete the entry',
  },

  logview: {
    scroll_to_bottom: 'Scroll to bottom',
  },

  master_interrupt: 'master interrupted',
  master_desc:
    'The master process is responsible for inter-policy process communication and resource configuration, please restart the application',

  ledger_interrupt: 'ledger interrupted',
  ledger_desc:
    'Accounting services are responsible for position and capital calculations, please restart the application',

  cached_interrupt: 'cached interrupted',
  cached_desc:
    'The storage service is responsible for data landing. The storage service disconnection does not affect transactions, please restart the application after the transaction',

  state_interrupt_msg: '{state} has been disconnected',
  state_interrupt_desc:
    '{state} has been disconnected, transaction may be interrupted. Please check',

  kungfu: 'Kungfu',

  system_prompt: 'System Prompt',
  archive_done: 'Kungfu archive done',
  archive_loading: 'Kungfu archive loading...',
  environment_done: 'Kungfu environment done ✓',
  environment_loading: 'Kungfu environment loading...',
  extra_resources_done: 'Extra resources done ✓',
  extra_resouces_loading: 'Extra resources loading...',
  saving_data_done: 'Saving data done ✓',
  saving_data_loading: 'Saving data loading ...',
  end_all_transactions: 'End all transactions ✓',
  closing: 'End the transaction process, Please do not close...',

  quit_confirm:
    'Exiting the application ends all transactions, Confirm to exit?',
  restart_process:
    'Kungfu graphics process is interrupted. The interruption will not affect transactions. Do you want to restart the graphics process?',

  未就绪: '{processId} not ready, please try again later',
  系统外: 'Out-of-system',
  手动: 'manual',
  任务: 'task',

  正常: 'normal',
  异常: 'warn',
  错误: 'error',
  文件路径不存在: 'The file path does not exist',
  策略id不存在: 'The strategy id does not exist',

  可用仓位: 'Avail Pos',
  可用资金: 'Avail Asset',
  交易金额: 'Amount',
  保证金占用: 'Margin',
  保证金返还: 'Margin',
  剩余资金: 'Left Asset',
  剩余仓位: 'Left Pos',
};
