//
//  ONTTransaction.h
//  ONTWallet
//
//  Created by Yuzhiyou on 2018/7/23.
//  Copyright © 2018年 Yuzhiyou. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "ONTAddress.h"
#import "ONTAttribute.h"
#import "ONTSignature.h"

@class ONTAccount;

typedef NS_OPTIONS(NSInteger, ONTTransactionType){
    ONTTransactionTypeBookkeeping = 0x00,
    ONTTransactionTypeBookkeeper = 0x02,
    ONTTransactionTypeClaim = 0x03,
    ONTTransactionTypeEnrollment = 0x04,
    ONTTransactionTypeVote = 0x05,
    ONTTransactionTypeDeployCode = 0xd0,
    ONTTransactionTypeInvokeCode = 0xd1,
    ONTTransactionTypeTransferTransaction = 0x80
};

@interface ONTTransaction : NSObject

@property (nonatomic,assign) uint8_t version;
@property (nonatomic,assign) ONTTransactionType type;
@property (nonatomic,assign) int nonce;
@property (nonatomic,assign) long gasPrice;
@property (nonatomic,assign) long gasLimit;
@property (nonatomic,strong) ONTAddress *payer;
@property (nonatomic,strong) NSMutableArray<ONTAttribute *> *attributes;
@property (nonatomic,strong) NSMutableArray<ONTSignature *> *signatures;

/**
 * @brief Initialization method
 */
- (instancetype)initWithType:(ONTTransactionType)type;
/**
 * @brief Obtaining complete byte stream data
 */
- (NSData *)toByte;
/**
 * @brief Obtaining complete byte stream data
 */
- (NSData *)toRawByte;
/**
 * @brief Obtaining Exclusive byte stream data
 */
- (void)toExclusiveByte:(NSMutableData *)stream;

- (NSData *)getSignHash;

- (void)addSign:(ONTAccount *)signer;


/**
 构造 Invoke Transaction

 @param dic DAPP 返回的交易数据
 @return ONTTransaction 对象
 */
+ (ONTTransaction *)makeDappInvokeTransactionWithDic:(NSDictionary *)dic;



@end
