//
//  ONTAttribute.h
//  ONTWallet
//
//  Created by Yuzhiyou on 2018/7/24.
//  Copyright © 2018年 Yuzhiyou. All rights reserved.
//

#import <Foundation/Foundation.h>
typedef NS_OPTIONS(NSInteger, ONTAttributeUsage){
    // Constants
    ONTAttributeUsageNonce = 0x00,
    ONTAttributeUsageScript = 0x20,
    ONTAttributeUsageDescriptionUrl = 0x81,
    ONTAttributeUsageDescription = 0x90
};
@interface ONTAttribute : NSObject

@property (nonatomic,assign) ONTAttributeUsage usage;
@property (nonatomic,strong) NSData *data;
@property (nonatomic,assign) int size;

/**
 * @brief Obtaining complete byte stream data
 */
- (void)toByte:(NSMutableData *)stream;
@end
