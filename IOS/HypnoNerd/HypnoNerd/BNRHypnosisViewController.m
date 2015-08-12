//
//  BNRHypnosisViewController.m
//  HypnoNerd
//
//  Created by sijiewang on 8/11/15.
//  Copyright (c) 2015 lnmcc. All rights reserved.
//

#import "BNRHypnosisViewController.h"

@implementation BNRHypnosisViewController

- (instancetype)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil {
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        self.tabBarItem.title = @"Hypnotize";
        UIImage *i = [UIImage imageNamed:@"hypnosis"];
        self.tabBarItem.image = i;
    }
    return self;
}

- (void)loadView {
    BNRHypnosisterView *backgroundView = [[BNRHypnosisterView alloc]init];
    self.view = backgroundView;
}

@end
