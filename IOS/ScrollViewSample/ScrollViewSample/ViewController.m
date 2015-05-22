//
//  ViewController.m
//  ScrollViewSample
//
//  Created by sijiewang on 5/21/15.
//  Copyright (c) 2015 lnmcc. All rights reserved.
//

#import "ViewController.h"

@interface ViewController ()

@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view, typically from a nib.
    self.scrollView.contentSize = CGSizeMake(320, 1000);
    self.textField.delegate = self;
}

- (void)viewDidAppear:(BOOL)animated {
    [self.scrollView setContentOffset:CGPointMake(0, 110) animated:YES];
    [super viewDidAppear:YES];
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (void)keyboardDidShow: (NSNotification*) notif {
    if (keyboardVisible) {
        return;
    }
    NSDictionary *info = [notif userInfo];
    NSValue *aValue = [info objectForKey:UIKeyboardFrameEndUserInfoKey];
    CGSize keyboardSize = [aValue CGRectValue].size;
    
    CGRect viewFrame = self.scrollView.frame;
    viewFrame.size.height -= (keyboardSize.height);
    self.scrollView.frame = viewFrame;
    
    CGRect textFieldRect = [self.textField frame];
    [self.scrollView scrollRectToVisible:textFieldRect animated:YES];
    keyboardVisible = YES;
}

- (void)keyboardDidHide: (NSNotification *)notif {
    NSDictionary *info = [notif userInfo];
    NSValue *aValue = [info objectForKey:UIKeyboardFrameEndUserInfoKey];
    CGSize keyboardSize = [aValue CGRectValue].size;
    
    CGRect viewFrame = self.scrollView.frame;
    viewFrame.size.height += keyboardSize.height;
    self.scrollView.frame = viewFrame;
    
    if (!keyboardVisible) {
        return;
    }
    keyboardVisible = NO;
}

@end
