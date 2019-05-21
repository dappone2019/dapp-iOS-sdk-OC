//
//  ONTAccount.h
//  ONTWallet
//
//  Created by Yuzhiyou on 2018/7/13.
//  Copyright © 2018年 Yuzhiyou. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "ONTPublicKey.h"
#import "ONTPrivateKey.h"
#import "ONTAddress.h"




typedef NS_ENUM(NSUInteger, ONTTokenType) {
    ONTTokenTypeONT,
    ONTTokenTypeONG,
};

#define ONT_CONTRACT @"0000000000000000000000000000000000000001"
#define ONG_CONTRACT @"0000000000000000000000000000000000000002"

/**
 数字资产
 */
@interface ONTAccount : NSObject <NSCoding>

@property (nonatomic, readonly) NSString *name;
@property (nonatomic, readonly) NSString *mnemonicText;
@property (nonatomic, readonly) NSString *encryptMnemonicText;
@property (nonatomic, readonly) NSString *privateKeyHex;
@property (nonatomic, readonly) NSString *wif;
@property (nonatomic, readonly) NSString *keystore;
@property (nonatomic, readonly) ONTPrivateKey *privateKey;
@property (nonatomic, readonly) ONTPublicKey *publicKey;
@property (nonatomic, readonly) ONTAddress *address;

/**
 随机创建一个钱包

 @param name 钱包名字
 @param password 钱包密码
 @return ONTAccount
 */
- (instancetype)initWithName:(NSString *)name password:(NSString *)password;

/**
 通过助记词创建一个钱包

 @param name 钱包名字
 @param password 钱包密码
 @param mnemonicText 助记词（以空格分隔开）
 @return ONTAccount
 */
- (instancetype)initWithName:(NSString *)name password:(NSString *)password mnemonicText:(NSString *)mnemonicText;

/**
 通过明文私钥创建一个钱包

 @param name 钱包名字
 @param password 钱包密码
 @param privateKeyHex 明文私钥（十六进制的64位私钥）
 @return ONTAccount
 */
- (instancetype)initWithName:(NSString *)name password:(NSString *)password privateKeyHex:(NSString *)privateKeyHex;

/**
 通过 WIF 创建一个钱包

 @param name 钱包名字
 @param password 钱包密码
 @param wif WIF（钱包导入格式）
 @return ONTAccount
 */
- (instancetype)initWithName:(NSString *)name password:(NSString *)password wif:(NSString *)wif;

/**
 通过 Keystore 和 密码 创建一个钱包

 @param name 钱包名字（可不传，用 Keystore 里的 label 字段作为 name）
 @param password 钱包密码
 @param keystore Keystore JSON 字符串
 @return ONTAccount
 */
- (instancetype)initWithName:(NSString *)name password:(NSString *)password keystore:(NSString *)keystore;


/**
 构造 ONT、ONG 交易

 @param tokenType ONT、ONG
 @param toAddress 收款地址
 @param amount 转账金额
 @param gasPrice 默认 500
 @param gasLimit 默认 20000
 @return TxHex
 */
- (NSString *)makeTransferTxWithToken:(ONTTokenType)tokenType toAddress:(NSString *)toAddress amount:(NSString *)amount gasPrice:(long)gasPrice gasLimit:(long)gasLimit;

/**
 构造提取 ONG 交易

 @param address 提取地址
 @param amount 提取金额
 @param gasPrice 默认 500
 @param gasLimit 默认 20000
 @return TxHex
 */
- (NSString *)makeClaimOngTxWithAddress:(NSString *)address amount:(NSString *)amount gasPrice:(long)gasPrice gasLimit:(long)gasLimit;

- (BOOL)isEqualToAccount:(ONTAccount *)other;

/**
 签名消息

 @param message 消息数据
 @return 签名后的 HexString
 */
- (NSString *)signMessage:(NSData *)message;

@end
