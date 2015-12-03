//
//  YDChatUser.h
//  YDChatApp
//
//  Created by sijiewang on 12/3/15.
//  Copyright © 2015 lnmcc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

@interface YDChatUser : NSObject

@property (nonatomic, strong) NSString *username;
@property (nonatomic, strong) UIImage *avatar;

- (instancetype)initWithUsername: (NSString *)user avatarImage: (UIImage *)image;

@end
