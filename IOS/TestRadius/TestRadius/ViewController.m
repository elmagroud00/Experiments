//
//  ViewController.m
//  TestRadius
//
//  Created by sijiewang on 12/29/15.
//  Copyright © 2015 lnmcc. All rights reserved.
//

#import "ViewController.h"

@interface ViewController ()
@property (weak, nonatomic) IBOutlet UIView *view1;
@property (weak, nonatomic) IBOutlet UIView *view2;

@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    self.view1.layer.cornerRadius = 20.0f;
    self.view2.layer.cornerRadius = 20.0f;
    self.view2.layer.masksToBounds = YES;
    self.view1.layer.borderWidth = 5.0f;
    
    self.view1.layer.shadowOpacity = 0.5;
    self.view1.layer.shadowOffset = CGSizeMake(0.0f, 5.0f);
    self.view1.layer.shadowRadius = 5.0f;
    CGMutablePathRef ciclePath = CGPathCreateMutable();
    CGPathAddEllipseInRect(ciclePath, NULL, self.view1.bounds);
    self.view1.layer.shadowPath = ciclePath;
    CGPathRelease(ciclePath);
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

@end
