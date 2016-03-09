//
//  NSNotificationCenter+MG.m
//  TestNSNotificationCenterThread
//
//  Created by sijiewang on 3/2/16.
//  Copyright © 2016 lnmcc. All rights reserved.
//

#import "NSNotificationCenter+MG.h"

@implementation NSNotificationCenter (MG)

-(void)mgPostNotificationNameOnMainThread:(NSString *)notificationName object:(id)obj userInfo:(NSDictionary *)userInfo {
    if (![NSThread isMainThread]) {
        dispatch_async(dispatch_get_main_queue(), ^{
            [self postNotificationName:notificationName object:obj userInfo:userInfo];
        });
    } else {
        [self postNotificationName:notificationName object:obj userInfo:userInfo];
    }
}

@end
