//
//  ViewController.m
//  ONTWalletDemo
//
//  Created by 区块链 on 2019/4/28.
//  Copyright © 2019 com.fengniaomall.ontwallet. All rights reserved.
//

#import "HomeViewController.h"
#import "DappbirdsSDK/DBWalletManager.h"
#import "DappbirdsSDK/MBProgressHUD+MBProgressHUD_show.h"

@interface HomeViewController ()  <UITableViewDelegate,UITableViewDataSource,UITextFieldDelegate>

@property (nonatomic, strong) UITableView * tableView;
@property (nonatomic, strong) NSArray * dataList;
@property (nonatomic, strong) UILabel * addressLabel;
@property (nonatomic, strong) UILabel * ongBalance;
@property (nonatomic, strong) UILabel * addressCopyLabel;
@property (nonatomic, assign) BOOL flagHasWallet;
@end


@implementation HomeViewController

- (NSArray *)dataList {
    if (_dataList == nil) {
        self.dataList = @[
                          @{@"title": @"查询", @"data": @[@"查看钱包"]},
                          @{@"title": @"支付", @"data": @[@"支付0.1个ONG"]},
                          @{@"title": @"查询", @"data": @[@"刷新余额"]},
                          ]; // @{@"title": @"我的", @"data": @[@"管理钱包"]},
    }
    return _dataList;
}

- (void)viewDidLoad {
    [super viewDidLoad];
    self.title = @"Dappbirds SDK";
    self.view.backgroundColor = BackgroundColor;
    
    // 初始化,必须
    [[DBWalletManager shared] setApp_id:@"1" openid:@"5X9qHSUPQgrZQ84mD188sd9kD3WkQN8vx" chain_type:@"7" debugMode:YES];
    
    [self initView];
    
    self.flagHasWallet = NO;
}

- (void)viewDidAppear:(BOOL)animated {
    [super viewDidAppear:animated];
    [self queryIsExitWallet];
    if (self.tableView != nil) {
        [self.tableView reloadData];
    }
}



- (void)initView {
    UITableView * tableView = [[UITableView alloc] initWithFrame: CGRectMake(0, NAVIGATION_HEIGHT, ScreenWidth, ScreenHeight - NAVIGATION_HEIGHT) style: UITableViewStyleGrouped];
    tableView.backgroundColor = BackgroundColor;
    tableView.delegate = self;
    tableView.dataSource = self;
    self.tableView = tableView;
    [self.view addSubview: tableView];
    
    UIView *headerView = [[UIView alloc]initWithFrame:CGRectMake(0, 0, ScreenWidth, 80)];
    headerView.backgroundColor = [UIColor whiteColor];
    
    CGFloat innerY = 0;
    
    UIView * sepView1 = [[UIView alloc] initWithFrame:CGRectMake(0, innerY, ScreenWidth, 20)];
    sepView1.backgroundColor = BackgroundColor;
    [headerView addSubview:sepView1];
    innerY += sepView1.frame.size.height;
    
    UILabel *ongBalance = [self getCommontTipsLabelWithText:@"ONG余额：暂无" innerY:innerY];
    ongBalance.textColor = BlackStyleColor;
    self.ongBalance = ongBalance;
    ongBalance.frame = CGRectMake(15, innerY, (ScreenWidth - 30) * 0.5 , 40);
    [headerView addSubview:ongBalance];
    
    UILabel *copyLabel = [self getCommontTipsLabelWithText:@"复制地址" innerY:innerY];
    self.addressCopyLabel = copyLabel;
    copyLabel.textColor = MainColor;
    copyLabel.userInteractionEnabled = YES;
    copyLabel.textAlignment = NSTextAlignmentRight;
    UITapGestureRecognizer *tapCopy = [[UITapGestureRecognizer alloc]initWithTarget:self action:@selector(onTapCreatWalletOrCopy)];
    [copyLabel addGestureRecognizer:tapCopy];
    copyLabel.frame = CGRectMake(ScreenWidth * 0.5, innerY, (ScreenWidth - 30) * 0.5 , 40);
    [headerView addSubview:copyLabel];
    
    innerY += ongBalance.frame.size.height ;
    
    
    UILabel *addressTitle = [self getCommontTipsLabelWithText:@"钱包地址：" innerY:innerY];
    addressTitle.frame = CGRectMake(15, innerY, 75, 40);
    addressTitle.textColor = BlackStyleColor;
    [headerView addSubview:addressTitle];
    
    UILabel *addressLabel = [self getCommontTipsLabelWithText:@"address" innerY:0];
    addressLabel.textColor = BlackStyleColor;
    addressLabel.frame = CGRectMake(90, innerY, ScreenWidth - 90, 40);
    self.addressLabel = addressLabel;
    self.addressLabel.userInteractionEnabled = YES;
    UITapGestureRecognizer *tap = [[UITapGestureRecognizer alloc]initWithTarget:self action:@selector(onTapCreatWalletOrCopy)];
    [self.addressLabel addGestureRecognizer:tap];
    [headerView addSubview:addressLabel];
    innerY += addressTitle.frame.size.height ;
    
    UIView * sepView = [[UIView alloc] initWithFrame:CGRectMake(0, innerY, ScreenWidth, 20)];
    sepView.backgroundColor = BackgroundColor;
    [headerView addSubview:sepView];
    innerY += sepView.frame.size.height;
    
    headerView.frame = CGRectMake(0, 0, ScreenWidth, innerY);
    self.tableView.tableHeaderView = headerView;
}

- (void)onTapCreatWalletOrCopy {
    if (self.flagHasWallet) {
        [self copyAddress];
    } else {
        [self modalToCreateWalletVC];
    }
}

- (void)copyAddress {
    UIPasteboard *pasteboard = [UIPasteboard generalPasteboard];
    pasteboard.string = self.addressLabel.text;
    [MBProgressHUD showSuccess:@"地址复制成功"];
    NSLog(@"%@",pasteboard.string);
}

- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView {
    return self.dataList.count;
}

-(NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section {
    NSArray * sectionData = self.dataList[section][@"data"];
    return sectionData.count;
}

- (CGFloat)tableView:(UITableView *)tableView heightForHeaderInSection:(NSInteger)section {
    return 0.0001;
}

- (UIView *)tableView:(UITableView *)tableView viewForHeaderInSection:(NSInteger)section {
    return [[UIView alloc]init];
}

- (CGFloat)tableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath {
    return 45;
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {
    static NSString * cellID = @"HomeTableCellID";
    UITableViewCell * cell = [tableView dequeueReusableCellWithIdentifier: cellID];
    if (cell == nil) {
        cell = [[UITableViewCell alloc] initWithStyle:UITableViewCellStyleDefault reuseIdentifier: cellID];
    }
    cell.textLabel.font = [UIFont systemFontOfSize:14];
    NSArray * data = self.dataList[indexPath.section][@"data"];
    cell.accessoryType = UITableViewCellAccessoryDisclosureIndicator;
    cell.textLabel.text = data[indexPath.row];
    return cell;
}


- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath {
    if (self.flagHasWallet) {
        if (indexPath.section == 0) {
            // 查看钱包明细
            [self modalToQueryWalletViewController];
        } else if (indexPath.section == 1) {
            // 支付ong
            [self modalToPayViewController];
        }else if (indexPath.section == 2) {
            // 更新余额
            [self getBalanceWithAddress];
        }
    } else {
        [self alertCreateWalletActionMsg: @"您还没有钱包，是否立刻创建？" title: @"提示"];
        
    }
}

/**
 * 1.查询当前钱包余额
 */
- (void)getBalanceWithAddress {
    [[DBWalletManager shared] getCurrentWalletBalanceCallback:^(NSDictionary *balanceDict, NSError *error) {
        self.ongBalance.text = [NSString stringWithFormat:@"ONG余额: %@", balanceDict[@"ONG"]];
    }];
}

/**
 * 2.查询是否存在钱包
 */
- (void)queryIsExitWallet {
    [[DBWalletManager shared] getAccountCallBack:^(BOOL hasWallet, NSString *address, NSString *msg) {
        self.flagHasWallet = hasWallet;
        if (hasWallet && self.addressLabel != nil) {
            self.addressLabel.text = [NSString stringWithFormat:@"%@",address];
            self.addressLabel.textColor = BlackStyleColor;
            [self getBalanceWithAddress];
            self.addressCopyLabel.hidden = NO;
        } else {
            self.addressLabel.text = @"暂无钱包，点击创建";
            self.addressLabel.textColor = MainColor;
            self.addressCopyLabel.hidden = YES;
            self.ongBalance.text = @"ONG余额：暂无";
        }
    }];
}

/**
 * 3.创建钱包
 */
- (void)modalToCreateWalletVC {
    // modal创建钱包页面
    [[DBWalletManager shared] createdNewWallet];
    
    // 获取用户创建钱包的回调 （成功后开发者保存地址）
    [DBWalletManager shared].accountCallBack = ^(BOOL success, NSString *address, NSString *msg) {
        NSLog(@"msg = %@", msg);
        NSLog(@"success = %d", success);
        if (success) {
            NSLog(@"address = %@", address);
            [MBProgressHUD showMessage:@"创建成功"];
        }
    };
}

/**
 * 4.统一支付
 */
- (void)modalToPayViewController {
    int random = arc4random() % 1000000;
    NSString *order_no = [NSString stringWithFormat:@"ordernomber%d", random];
    [[DBWalletManager shared] createdPayWalletWithContract_address:@"48628e2aa44a7e7f2d8e9fbe4001d731713789ca" _signature:@"cf38f9b6d2dc07784e727066f2fdac77" order_no:order_no amount:@"0.1" _timestamp:@"1556543707"];
    
    [DBWalletManager shared].payCallBack = ^(BOOL success, NSString *msg) {
        if (success) {
            NSLog(@"支付成功");
            [MBProgressHUD showMessage:@"支付成功"];
        }
    };
}

/**
 * 5.查看钱包明细
 */
- (void)modalToQueryWalletViewController {
    [[DBWalletManager shared] queryWalletDetails];
}

- (void)alertCreateWalletActionMsg: (NSString *)msg title: (NSString *)title {
    
    UIAlertController * alertVC = [UIAlertController alertControllerWithTitle: title message: msg preferredStyle: UIAlertControllerStyleAlert];
    [alertVC addAction:[UIAlertAction actionWithTitle: @"去创建" style: UIAlertActionStyleDefault handler:^(UIAlertAction * _Nonnull action) {
        [self modalToCreateWalletVC];
    }]];
    [alertVC addAction:[UIAlertAction actionWithTitle: @"取消" style: UIAlertActionStyleCancel handler: nil]];
    [self presentViewController:alertVC animated: YES completion: nil];
    
}

- (UILabel *)getCommontTipsLabelWithText:(NSString *)text innerY:(CGFloat)innerY{
    UILabel * titleLabel = [[UILabel alloc]initWithFrame:CGRectMake(15, innerY, ScreenWidth - 15, 40)];
    titleLabel.text = text;
    titleLabel.textColor = GrayStyleColor;
    titleLabel.font = [UIFont systemFontOfSize:13];
    return titleLabel;
}

- (UITextField *)getCommonTextFieldWithPlaceholder:(NSString *)placeHolder innerY:(CGFloat)innerY {
    UITextField *textField = [[UITextField alloc]init];
    textField.backgroundColor = [UIColor whiteColor];
    textField.font = [UIFont systemFontOfSize:12];
    textField.attributedPlaceholder = [[NSAttributedString alloc]initWithString:placeHolder attributes:@{NSForegroundColorAttributeName : [UIColor grayColor]}];
    UIView *leftView = [[UIView alloc]initWithFrame:CGRectMake(0, 0, 15, 40)];
    textField.leftView = leftView;
    textField.leftViewMode = UITextFieldViewModeAlways;
    textField.frame = CGRectMake(0, innerY, ScreenWidth, 40);
    
    return textField;
}


@end
