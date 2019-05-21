//
//  ONTRpcApi.h
//  ONTWallet
//
//  Created by zhangyutao on 2018/8/4.
//  Copyright © 2018年 zhangyutao. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "ONTTransactionNotifyInfo.h"

@interface ONTRpcApi : NSObject

@property (nonatomic, strong) NSString *rpcURL;

+ (instancetype)shareInstance;

//得到主链上的最高区块的哈希
- (void)getBestBlockHashCallback:(void (^)(NSString *txHash, NSError *error))callback;

//通过区块哈希得到区块(verbose为可选参数，默认值为0，可选值为1)
- (void)getBlockWithTxHash:(NSString *)txHash verbose:(BOOL)verbose callback:(void (^)(id result, NSError *error))callback;

//通过区块高度得到区块(verbose为可选参数，默认值为0，可选值为1)
- (void)getBlockWithHeight:(long)height verbose:(BOOL)verbose callback:(void (^)(id result, NSError *error))callback;

//得到主链上的区块总量
- (void)getBlockCountCallback:(void (^)(NSInteger blockCount, NSError *error))callback;
+ (void)getBlockCountWithUrl:(NSString *)urlString callback:(void (^)(NSInteger blockCount, NSError *error))callback;

//得到对应高度的区块的哈希
- (void)getBlockHashWithHeight:(long)height callback:(void (^)(NSString *txHash, NSError *error))callback;

//得到当前网络上连接的节点数
- (void)getConnectionCountCallback:(void (^)(NSInteger connectionCount, NSError *error))callback;
+ (void)getConnectionCountWithUrl:(NSString *)urlString callback:(void (^)(NSInteger connectionCount, NSError *error))callback;

//通过交易哈希得到交易详情
- (void)getRawtransactionWithTxHash:(NSString *)txHash verbose:(BOOL)verbose callback:(void (^)(id result, NSError *error))callback;

//向网络中发送交易(发送的数据为签过名的交易序列化后的十六进制字符串)
- (void)sendRawtransactionWithHexTx:(NSString *)hexTx preExec:(BOOL)preExec callback:(void (^)(NSString *txHash, NSError *error))callback;
- (void)dappSendRawtransactionWithHexTx:(NSString *)hexTx preExec:(BOOL)preExec callback:(void (^)(ONTTransactionNotifyInfo *notifyInfo, id responseObject, NSError *error))callback;

//根据合约地址和存储的键，得到对应的值
- (void)getStorageWithScriptHash:(NSString *)scriptHash key:(NSString *)key callback:(void (^)(id result, NSError *error))callback;

//得到运行的ontology版本
- (void)getVersionCallback:(void (^)(id result, NSError *error))callback;

//根据合约地址，得到合约信息
- (void)getContractStateWithScriptHash:(NSString *)scriptHash verbose:(BOOL)verbose callback:(void (^)(id result, NSError *error))callback;

//查询内存中的交易的数量
- (void)getMempoolTxCountCallback:(void (^)(id result, NSError *error))callback;

//查询内存中的交易的状态
- (void)getMempoolTxStateWithTxHash:(NSString *)txHash callback:(void (^)(id result, NSError *error))callback;

//得到智能合约执行的结果
- (void)getSmartCodeEventWithTxHash:(NSString *)txHash callback:(void (^)(NSInteger state, NSError *error))callback;
- (void)getSmartCodeEventWithBlockHeight:(long)height callback:(void (^)(id result, NSError *error))callback;

//得到该交易哈希所落账的区块的高度
- (void)getBlockHeightWithTxhash:(NSString *)txHash callback:(void (^)(id result, NSError *error))callback;

//返回base58地址的余额
- (void)getBalanceWithAddress:(NSString *)address callback:(void (^)(NSArray *balances, NSError *error))callback;

//返回merkle证明
- (void)getMerkleProofWithTxHash:(NSString *)txHash callback:(void (^)(id result, NSError *error))callback;

//返回gas的价格
- (void)getGaspriceCallback:(void (^)(NSString *gasprice, NSError *error))callback;

//返回允许从from转出到to账户的额度
- (void)getAllowanceWithAsset:(NSString *)asset fromAddress:(NSString *)fromAddress toAddress:(NSString *)toAddress callback:(void (^)(id result, NSError *error))callback;

//返回该账户未提取的ong
- (void)getUnboundOng:(NSString *)address callback:(void (^)(NSString *amount, NSError *error))callback;

//返回该高度对应的区块落账的交易的哈希
- (void)getBlockTxsWithHeight:(long)height callback:(void (^)(id result, NSError *error))callback;

//获取 network id
- (void)getNetworkIDCallback:(void (^)(id result, NSError *error))callback;

@end
