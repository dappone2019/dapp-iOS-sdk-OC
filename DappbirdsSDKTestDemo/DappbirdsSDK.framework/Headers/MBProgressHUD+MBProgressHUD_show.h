//
//  MBProgressHUD+MBProgressHUD_show.h
//  TXLiteAVDemo_Professional
//
//  Created by 区块链 on 2018/11/24.
//  Copyright © 2018 Tencent. All rights reserved.
//

#import "MBProgressHUD.h"


@interface MBProgressHUD (MBProgressHUD_show)
#define kHudShowTime 1.5
#pragma mark 在指定的view上显示hud
+ (void)showMessage:(NSString *)message toView:(UIView *)view;
+ (void)showSuccess:(NSString *)success toView:(UIView *)view;
+ (void)showError:(NSString *)error toView:(UIView *)view;
+ (void)showWarning:(NSString *)Warning toView:(UIView *)view;
+ (void)showMessageWithImageName:(NSString *)imageName message:(NSString *)message toView:(UIView *)view;
+ (MBProgressHUD *)showActivityMessage:(NSString*)message view:(UIView *)view;
+ (MBProgressHUD *)showProgressBarToView:(UIView *)view WithMsg:(NSString *)msg;

#pragma mark 在window上显示hud
+ (void)showMessage:(NSString *)message;
+ (void)showSuccess:(NSString *)success;
+ (void)showError:(NSString *)error;
+ (void)showWarning:(NSString *)Warning;
+ (void)showMessageWithImageName:(NSString *)imageName message:(NSString *)message;
+ (MBProgressHUD *)showActivityMessage:(NSString*)message;
+ (MBProgressHUD *)showProgressBarToWindowWithMsg:(NSString *)msg;


#pragma mark 移除hud
+ (void)hideHUDForView:(UIView *)view;
+ (void)hideHUD;
+ (void)hideWindowHUD;
@end
