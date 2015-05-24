//
//  ViewController.m
//  NavigationBarSample
//
//  Created by sijiewang on 5/23/15.
//  Copyright (c) 2015 lnmcc. All rights reserved.
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

- (IBAction)sava:(UIBarButtonItem *)sender {
    self.label.text = @"点击Sava";
}

- (IBAction)add:(UIBarButtonItem *)sender {
    self.label.text = @"点击Add";
}
@end
