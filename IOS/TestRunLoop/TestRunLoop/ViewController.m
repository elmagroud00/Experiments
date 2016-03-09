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

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view, typically from a nib.
    end = NO;
    
    NSLog(@"start new thread ...");
    [NSThread detachNewThreadSelector:@selector(runOnNewThread) toTarget:self withObject:nil];
    while (!end) {
        NSLog(@"runloop ...");
        [[NSRunLoop currentRunLoop] runMode:NSDefaultRunLoopMode beforeDate:[NSDate distantFuture]];
        NSLog(@"runloop end.");
    }
    NSLog(@"ok");
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
