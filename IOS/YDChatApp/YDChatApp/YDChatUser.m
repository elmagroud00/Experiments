//
//  YDChatUser.m
//  YDChatApp
//
//  Created by sijiewang on 12/3/15.
//  Copyright © 2015 lnmcc. All rights reserved.
//

#import "YDChatUser.h"

@implementation YDChatUser
@synthesize avatar = _avatar;
@synthesize username = _username;

- (instancetype)initWithUsername:(NSString *)user avatarImage:(UIImage *)image {
    self = [super init];
    if (self) {
        self.avatar = [image copy];
        self.username = [user copy];
    }
    return self;
}

@end
