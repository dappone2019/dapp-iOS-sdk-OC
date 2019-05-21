//
//  ONTAddress.h
//  ONTWallet
//
//  Created by Yuzhiyou on 2018/7/24.
//  Copyright © 2018年 Yuzhiyou. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface ONTAddress : NSObject

@property (nonatomic,readonly) NSString *address;
@property (nonatomic,readonly) NSData *publicKeyHash160;

+ (instancetype)addressWithString:(NSString*)addressString;

/**
 * @brief Initialization method
 */
- (instancetype)initWithAddressString:(NSString*)addressString;
/**
 * @brief Initialization method
 */
- (instancetype)initWithData:(NSData*)data;

- (NSString *)generateOntid;

@end
