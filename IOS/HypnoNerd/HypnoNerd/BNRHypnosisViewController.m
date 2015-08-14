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
    CGRect frame = [UIScreen mainScreen].bounds;
    //BNRHypnosisterView *backgroundView = [[BNRHypnosisterView alloc]init];
    BNRHypnosisterView *backgroundView = [[BNRHypnosisterView alloc]initWithFrame:frame];
    
    CGRect textFieldRect = CGRectMake(40, 70, 240, 30);
    UITextField *textField = [[UITextField alloc]initWithFrame:textFieldRect];
    
    textField.borderStyle = UITextBorderStyleRoundedRect;
    textField.placeholder = @"Hypnotize me";
    textField.returnKeyType = UIReturnKeyDone;
    textField.delegate = self;
    
    [backgroundView addSubview:textField];
    
    self.view = backgroundView;
}

- (void)drawHypnoticMessage:(NSString *)message {
    for (int i = 0; i < 20; i++) {
        UILabel *messageLabel = [[UILabel alloc]init];
        
        messageLabel.backgroundColor = [UIColor clearColor];
        messageLabel.textColor = [UIColor redColor];
        messageLabel.text = message;
        
        [messageLabel sizeToFit];
        
        int width = (int)(self.view.bounds.size.width - messageLabel.bounds.size.width);
        int x = arc4random() % width;
        
        int height = (int)(self.view.bounds.size.height - messageLabel.bounds.size.height);
        int y = arc4random() % height;
        
        CGRect frame = messageLabel.frame;
        frame.origin = CGPointMake(x, y);
        messageLabel.frame = frame;
        
        [self.view addSubview:messageLabel];
    }
}

- (BOOL)textFieldShouldReturn:(UITextField *)textField {
    NSLog(@"%@", textField.text);
    [self drawHypnoticMessage:textField.text];
    
    textField.text = @"";
    [textField resignFirstResponder];
    return YES;
}

@end
