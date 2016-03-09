//
//  MyObserved.m
//  TestNSNotificationCenterThread
//
//  Created by sijiewang on 3/2/16.
//  Copyright © 2016 lnmcc. All rights reserved.
//

#import "MyObserved.h"
#import "NSNotificationCenter+MG.h"

@implementation MyObserved

-(id)init {
    self = [super init];
    if (self != nil) {
        [self performSelectorInBackground:@selector(postNotification) withObject:nil];
    }
    return self;
}

-(void)postNotification {
    NSLog(@"MyObserved Thread: %@", [NSThread currentThread]);
    [[NSNotificationCenter defaultCenter] mgPostNotificationNameOnMainThread:@"MyNotification" object:self userInfo:nil];
}

@end
