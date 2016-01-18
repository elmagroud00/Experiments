//
//  ViewController.m
//  TestNSRunLoop
//
//  Created by sijiewang on 1/14/16.
//  Copyright © 2016 lnmcc. All rights reserved.
//

#import "ViewController.h"
#import "MyTask.h"

@interface ViewController ()

@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    
    NSOperationQueue *queue = [[NSOperationQueue alloc] init];
    MyTask *myTask = [[MyTask alloc] init];
    [queue addOperation:myTask];
    MyTask *myTask1 = [[MyTask alloc] init];
    [queue addOperation:myTask1];
    MyTask *myTask2 = [[MyTask alloc] init];
    [queue addOperation:myTask2];
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

@end
