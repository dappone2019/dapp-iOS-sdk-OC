//
//  ONTPublicKey.h
//  ONTWallet
//
//  Created by Yuzhiyou on 2018/7/13.
//  Copyright © 2018年 Yuzhiyou. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "ONTAddress.h"

@interface ONTPublicKey : NSObject

/**
 * @brief Initialization method
 */
- (instancetype)initWithData:(NSData*)pubKey;

-(NSData *)data;
- (ONTAddress*)toAddress;
@end
