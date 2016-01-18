//
//  MyTask.m
//  TestNSRunLoop
//
//  Created by sijiewang on 1/14/16.
//  Copyright © 2016 lnmcc. All rights reserved.
//

#import "MyTask.h"

@implementation MyTask
    
- (void)main {
    NSLog(@"Begin Thread = %@", self);
    NSTimer *timer = [NSTimer timerWithTimeInterval: 2 target:self selector:@selector(handleTime:) userInfo:nil repeats:NO];
    [timer fire];
    while (!didDisconnect) {
        [[NSRunLoop currentRunLoop] runMode:NSDefaultRunLoopMode beforeDate: [NSDate distantFeature]];
    }
}

- (void)handleTime:(id)sender {
    NSLog(@"Invoked NSTimer");
}

- (void) dealloc {
    NSLog(@"delloc mytask = %@", self);
}

@end
