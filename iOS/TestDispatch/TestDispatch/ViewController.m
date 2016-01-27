//
//  ViewController.m
//  TestDispatch
//
//  Created by sijiewang on 1/25/16.
//  Copyright © 2016 lnmcc. All rights reserved.
//

#import "ViewController.h"

@interface ViewController ()

@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view, typically from a nib.
    static dispatch_once_t pred = 0;
    dispatch_once(&pred, ^{
        NSLog(@"At dispatch_once");
        [NSThread sleepForTimeInterval:10];
    });
    NSLog(@"ViewDidLoad Finish");
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

@end
