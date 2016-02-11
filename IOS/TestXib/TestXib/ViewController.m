//
//  ViewController.m
//  TestXib
//
//  Created by sijiewang on 2/4/16.
//  Copyright © 2016 lnmcc. All rights reserved.
//

#import "ViewController.h"
#import "TestXibViewController.h"
#import "MediaControl.h"

@interface ViewController () {
    TestXibViewController *testXibVC;
    MediaControl *mediaControl;
}
@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    //[self loadMediaView];
}

- (void)loadMediaView {
    mediaControl = [[MediaControl alloc] initWithFrame:self.view.frame];
    [self.view addSubview:mediaControl];
}

- (void)loadTestXibView {
    testXibVC = [[TestXibViewController alloc] init];
    testXibVC.view.frame = self.view.frame;
    [self.view addSubview:testXibVC.view];
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

@end
