//
//  ONTPrivateKey.h
//  ONTWallet
//
//  Created by Yuzhiyou on 2018/7/13.
//  Copyright © 2018年 Yuzhiyou. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface ONTPrivateKey : NSObject
/**
 * @brief Initialization method
 */
- (instancetype) initWithData:(NSData *)privKey;
/**
 * @brief Initialization method
 */
- (instancetype) initWithPrivateKeyHex:(NSString *)privKeyHex;
/**
 * @brief Initialization method
 */
- (instancetype) initWithWif:(NSString *)wif;
/**
 * @return ONT Private to Wif
 */
- (NSString *)toWif;
/**
 * @return ONT Private Data
 */
-(NSData *)data;

@end
