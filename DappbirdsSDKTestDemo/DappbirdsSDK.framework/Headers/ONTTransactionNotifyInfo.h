//
//  ONTTransactionNotifyInfo.h
//  MediSharesiOS
//
//  Created by zhangyutao on 2018/12/26.
//  Copyright © 2018 zhongtuobang. All rights reserved.
//

#import <Foundation/Foundation.h>

@class ONTTransactionNotify;
@class ONTTransactionState;

@interface ONTTransactionNotifyInfo : NSObject

@property(nonatomic, strong) id result;
@property(nonatomic, assign) NSInteger state;
@property(nonatomic, assign) NSInteger gas;
@property(nonatomic, strong) NSMutableArray<ONTTransactionNotify *> *notify;

+ (ONTTransactionNotifyInfo *)initWithDic:(NSDictionary *)dic;

@end


@interface ONTTransactionNotify : NSObject

@property(nonatomic, strong) NSString *contractAddress;
@property(nonatomic, strong) ONTTransactionState *states;

@end


@interface ONTTransactionState : NSObject

@property(nonatomic, strong) NSString *func;
@property(nonatomic, strong) NSString *from;
@property(nonatomic, strong) NSString *to;
@property(nonatomic, strong) NSString *amount;

@end



