//
//  MyObserver.m
//  TestNSNotificationCenterThread
//
//  Created by sijiewang on 3/2/16.
//  Copyright © 2016 lnmcc. All rights reserved.
//

#import "MyObserver.h"

@implementation MyObserver

-(void)observedNotification:(NSNotificationCenter *)notification {
    NSLog(@"begin %@", self);
    NSLog(@"MyObserver Thread: %@", [NSThread currentThread]);
    sleep(1);
    NSLog(@"end %@", self);
}

-(id)init {
    self = [super init];
    if (self != nil) {
        [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(observedNotification:) name:@"MyNotification" object:nil];
        _myObserved = [[MyObserved alloc] init];
    }
    return self;
}

-(void)dealloc {
    [[NSNotificationCenter defaultCenter] removeObserver:self];
    NSLog(@"dealloc %@", self);
}

@end
