//
//  ViewController.m
//  TestRunLoop
//
//  Created by sijiewang on 3/8/16.
//  Copyright © 2016 lnmcc. All rights reserved.
//

#import "ViewController.h"

@interface ViewController () {
    Boolean end;
}
@end

@implementation ViewController

static void myRunLoopObserver(CFRunLoopObserverRef observer, CFRunLoopActivity activity, void *info) {
    NSLog(@"runloop_callback");
}

- (void)doFireTimer {
    
}

- (void)threadMain {
    CFRunLoopObserverCallBack *myRunLoopObserver;
    // The application uses garbage collection, so no autorelease pool is needed.
    NSRunLoop* myRunLoop = [NSRunLoop currentRunLoop];
    // Create a run loop observer and attach it to the run loop.
    CFRunLoopObserverContext context = {0, (__bridge void *)(self), NULL, NULL, NULL};
    CFRunLoopObserverRef observer = CFRunLoopObserverCreate(kCFAllocatorDefault,kCFRunLoopAllActivities, YES, 0, (CFRunLoopObserverCallBack)&myRunLoopObserver, &context);
    if (observer){
        CFRunLoopRef cfLoop = [myRunLoop getCFRunLoop];
        CFRunLoopAddObserver(cfLoop, observer, kCFRunLoopDefaultMode);
    }
    // Create and schedule the timer.
    [NSTimer scheduledTimerWithTimeInterval:0.1 target:self selector:@selector(doFireTimer) userInfo:nil repeats:YES];
    NSInteger loopCount = 10;
    do{
        // Run the run loop 10 times to let the timer fire.
        [myRunLoop runUntilDate:[NSDate dateWithTimeIntervalSinceNow:1]];
        loopCount--;
    } while (loopCount);
}

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view, typically from a nib.
    end = NO;
    [self threadMain];
    /*
    NSLog(@"start new thread ...");
    [NSThread detachNewThreadSelector:@selector(runOnNewThread) toTarget:self withObject:nil];
    while (!end) {
        NSLog(@"runloop ...");
        [[NSRunLoop currentRunLoop] runMode:NSDefaultRunLoopMode beforeDate:[NSDate distantFuture]];
        NSLog(@"runloop end.");
    }
    NSLog(@"ok");*/
}

- (void)runOnNewThread {
    NSLog(@"run for new thread ...");
    sleep(2);
    [self performSelectorOnMainThread:@selector(setEnd) withObject:nil waitUntilDone:NO];
    NSLog(@"runOnNewThread end.");
}

- (void)setEnd {
    end = YES;
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

@end
