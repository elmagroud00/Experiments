//
//  NSNotificationCenter+MG.h
//  TestNSNotificationCenterThread
//
//  Created by sijiewang on 3/2/16.
//  Copyright © 2016 lnmcc. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface NSNotificationCenter (MG)

-(void)mgPostNotificationNameOnMainThread:(NSString *)notificationName object:(id)obj userInfo:(NSDictionary *)userInfo;

@end
