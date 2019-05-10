//
//  ONTManager.h
//  ONTWalletDemo
//
//  Created by 区块链 on 2019/4/29.
//  Copyright © 2019 com.fengniaomall.ontwallet. All rights reserved.
//

#import <Foundation/Foundation.h>
@class DBAccountModel;

typedef NS_OPTIONS(NSUInteger, CreatedWalletByType) {
    CreatedWalletByNew =     1 << 0,
    CreatedWalletByWif =  1 << 1,
    CreatedWalletByMnemonicText =    1 << 2,
    CreatedWalletByPrivateKey =   1 << 3,
    CreatedWalletByKeystore =   1 << 4
};


/**
 创建的回调
 */
typedef void (^AccountCompletionBlock)(BOOL success, NSString *addresss, NSString *msg);


/**
 支付的回调
 */
typedef void (^payCompletionBlock)(BOOL success, NSString * msg);



@interface DBWalletManager : NSObject
/**
 * 单例
 */
+ (DBWalletManager *)shared;

/**
 初始化设置
 @param app_id 参数appid
 @param openid 参数appid
 @param chain_type 链类型
 */
- (void)setApp_id:(NSString *)app_id openid:(NSString *)openid chain_type:(NSString *)chain_type debugMode:(BOOL)debug;


/**
 * 查询是否存在钱包,存在就回调出地址
 * hasWallet 是否存在钱包
 * address 该钱包地址
 */
- (void)getAccountCallBack:(void (^)(BOOL hasWallet, NSString *address, NSString * msg))callback;

/**
 * modal创建新的钱包页面
 */
- (void)createdNewWallet;

/**
 * 创建钱包结果的回调
 */
@property(nonatomic,copy) AccountCompletionBlock accountCallBack;



/**
 modal创建支付界面
 @param contract_address 合约地址
 @param _signature 签名串md5
 @param order_no 订单号
 @param amount 支付数量
 @param _timestamp 时间戳
 */
- (void)createdPayWalletWithContract_address:(NSString *)contract_address _signature:(NSString *)_signature order_no:(NSString *)order_no amount:(NSString *)amount _timestamp:(NSString *)_timestamp;

/**
 * 支付订单结果的回调
 */
@property(nonatomic,copy) payCompletionBlock payCallBack;

/**
 * modal钱包明细界面
 */
- (void)queryWalletDetails;




// SDK内部使用，开发者无需使用

/**
 * 创建钱包 或通过wif、mnemonic、privateKey导入钱包
 */
- (void)creatWalletType:(CreatedWalletByType)type WithName:(NSString *)name password:(NSString *)pwd wif:(NSString *)wif mnemonic:(NSString *)mnemonic privateKey:(NSString *)privateKey keystore:(NSString *)keystore callback:(void (^)(BOOL success, NSString *msg))callback ;

/**
 * 通过keyStore导入钱包
 */
- (void)creatWalletWithName:(NSString *)name password:(NSString *)pwd keyStore:(NSString *)keyStore callback:(void (^)(BOOL success, NSString *address, NSString *msg))callback ;

/**
 * 查询当前账户的交易明细
 */
- (void)getCurrentWalletBalanceCallback:(void (^)(NSDictionary *balanceDict, NSError *error))callback;

/**
 * 统一支付接口
 */
- (void)unitePayWithFrom_address:(NSString *)from_address contract_address:(NSString *)contract_address _signature:(NSString *)_signature order_no:(NSString *)order_no amount:(NSString *)amount _timestamp:(NSString *)_timestamp;

/**
 * 获取存储的account
 */
- (DBAccountModel *)getDBAccountModel;

/**
 * 删除存储的account
 */
- (void)deleteAccountmodel;

/**
 * 支付订单成功dismiss的回调
 */
@property(nonatomic,copy) payCompletionBlock paySuccessAndDismissCallBack;


@end

