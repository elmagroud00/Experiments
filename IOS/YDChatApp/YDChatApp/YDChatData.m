//
//  YDChatData.m
//  YDChatApp
//
//  Created by sijiewang on 12/1/15.
//  Copyright © 2015 lnmcc. All rights reserved.
//

#import "YDChatData.h"
#import <QuartzCore/QuartzCore.h>
#import <UIKit/UIKit.h>

@implementation YDChatData

const UIEdgeInsets textInsetsMine = {5, 10, 11, 17};
const UIEdgeInsets textInsetsSomeone = {5, 15, 11, 10};
const UIEdgeInsets imageInsetsMine = {11, 13, 16, 22};
const UIEdgeInsets imageInsetsSomeone = {11, 18, 16, 14};

#pragma initializers
+ (instancetype)dataWithText:(NSString *)text date:(NSDate *)date type:(YDChatType)type andUser:(YDChatUser *)_user {
    
    return [[YDChatData alloc] initWithText:text date:date type:type andUser:_user];
}

-(instancetype)initWithText:(NSString *)text date:(NSDate *)date type:(YDChatType)type andUser:(YDChatUser *)_user {
    
    UIFont *font = [UIFont boldSystemFontOfSize:12];
    int width = 225, height = 10000.0;
    NSMutableDictionary *atts = [[NSMutableDictionary alloc] init];
    [atts setObject:font forKey:NSFontAttributeName];
    CGRect size = [text boundingRectWithSize:CGSizeMake(width, height) options:NSStringDrawingUsesLineFragmentOrigin attributes:atts context:nil];
    UILabel *label = [[UILabel alloc] initWithFrame:CGRectMake(0, 0, size.size.width, size.size.height)];
    label.numberOfLines = 0;
    label.lineBreakMode = NSLineBreakByWordWrapping;
    label.text = (text ? text : @"");
    label.font = font;
    label.backgroundColor = [UIColor clearColor];
    UIEdgeInsets insets = (type == ChatTypeMine ? textInsetsMine : textInsetsSomeone);
    return [self initWithView:label date:date type:type andUser:_user insets:insets];
}

- (instancetype)initWithImage:(UIImage *)image date:(NSDate *)date type:(YDChatType)type andUser:(YDChatUser *)_user {
    
    CGSize size = image.size;
    if (size.width > 220) {
        size.height /= (size.width / 220);
        size.width = 220;
    }
    UIImageView *imageView = [[UIImageView alloc] initWithFrame:CGRectMake(0, 0, size.width, size.height)];
    imageView.image = image;
    imageView.layer.cornerRadius = 5.0;
    imageView.layer.masksToBounds = YES;
    UIEdgeInsets insets = (type == ChatTypeMine ? imageInsetsMine : imageInsetsSomeone);
    return [self initWithView:imageView date:date type:type andUser:_user insets:insets];
}

+ (instancetype)dateWithView:(UIView *)view date:(NSDate *)date type:(YDChatType)type andUser:(YDChatUser *)_user insets:(UIEdgeInsets)insets {
    
    return [[YDChatData alloc] initWithView:view date:date type:type andUser:_user insets:insets];
}

- (instancetype)initWithView:(UIView *)view date:(NSDate *)date type:(YDChatType)type andUser:(YDChatUser *)_user insets:(UIEdgeInsets)insets {
    
    self = [super init];
    if (self) {
        _chatUser = _user;
        _view = view;
        _date = date;
        _type = type;
        _insets = insets;
    }
    return self;
}

@end






















