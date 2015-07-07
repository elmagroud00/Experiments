//
//  ViewController.m
//  TestIndicator
//
//  Created by sijiewang on 7/7/15.
//  Copyright (c) 2015 lnmcc. All rights reserved.
//

#import "ViewController.h"

@interface ViewController ()

@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view, typically from a nib.
    self.navigationItem.leftBarButtonItem = self.editButtonItem;
    UIRefreshControl *rc = [[UIRefreshControl alloc]init];
    rc.attributedTitle = [[NSAttributedString alloc]initWithString:@"下拉刷新"];
    [rc addTarget:self action:nil forControlEvents:UIControlEventValueChanged];
    
    UIActivityIndicatorView *aiview = [[UIActivityIndicatorView alloc]initWithActivityIndicatorStyle:UIActivityIndicatorViewStyleGray];
    self.navigationItem.titleView = aiview;
    [aiview startAnimating];
    self.navigationItem.prompt = @"数据加载中....";
    
    [UIApplication sharedApplication].networkActivityIndicatorVisible = YES;
    
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

@end
