//
//  YDChatData.h
//  YDChatApp
//
//  Created by sijiewang on 12/1/15.
//  Copyright © 2015 lnmcc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

@class YDChatUser;

typedef enum _YDChatType {
    ChatTypeMine = 0,
    ChatTypeSomeone = 1
} YDChatType;

@interface YDChatData : NSObject

@property (readonly, nonatomic) YDChatType type;
@property (readonly, nonatomic, strong) NSDate *date;
@property (readonly, nonatomic, strong) UIView *view;
@property (readonly, nonatomic) UIEdgeInsets insets;
@property (nonatomic, strong) YDChatUser *chatUser;

+ (instancetype)dataWithText: (NSString *)text date: (NSDate *)date type: (YDChatType)type andUser: (YDChatUser *)_user;

+ (instancetype)dataWithImage: (UIImage *)image date:(NSDate *)date type: (YDChatType)type andUser:(YDChatUser *)_user;

+ (instancetype)dataWithView: (UIView *)view date:(NSDate *)date type: (YDChatType)type andUser:(YDChatUser *)_user insets:(UIEdgeInsets)insets;

@end