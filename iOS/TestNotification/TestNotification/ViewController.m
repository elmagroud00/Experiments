//
//  ViewController.m
//  TestNotification
//
//  Created by sijiewang on 2/21/16.
//  Copyright © 2016 lnmcc. All rights reserved.
//

#import "ViewController.h"

@interface ViewController ()

@end

@implementation ViewController

+ (void)initialize {
    NSLog(@"initialize");
}

+ (void)load {
    NSLog(@"load");
}

- (void)viewWillAppear:(BOOL)animated {

}

- (void)viewDidLoad {
    [super viewDidLoad];
    NSLog(@"viewWillAppear");
    [[NSNotificationCenter defaultCenter] addObserverForName:@"Test_NOTIY" object:self queue:[NSOperationQueue mainQueue] usingBlock:^(NSNotification * _Nonnull note) {
        NSLog(@"In Observer: Thread = %@", [NSThread currentThread]);
        [NSThread sleepForTimeInterval:5];
    }];
    
    dispatch_async(dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0), ^{
        NSLog(@"post: Thread = %@", [NSThread currentThread]);
        [[NSNotificationCenter defaultCenter] postNotificationName:@"Test_NOTIY" object:self];
        NSLog(@"at post thread");
    });
    //[[NSNotificationCenter defaultCenter] postNotificationName:@"Test_NOTIY" object:self];
    
    NSLog(@"in viewDidLoad...");
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (void)dealloc {
    NSLog(@"dealloc");
}

@end
