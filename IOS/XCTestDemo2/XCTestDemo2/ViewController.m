//
//  ViewController.m
//  XCTestDemo2
//
//  Created by sijiewang on 3/18/16.
//  Copyright © 2016 lnmcc. All rights reserved.
//

#import "ViewController.h"

@interface ViewController ()

@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view, typically from a nib.
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (NSString *)stringOutput {
    return @"wangsijie";
}

- (void)stringOutputAsync {
    dispatch_queue_t global_queue = dispatch_get_global_queue(
                                                              DISPATCH_QUEUE_PRIORITY_DEFAULT, 0);
    dispatch_async(global_queue, ^{
        
    });
}

@end