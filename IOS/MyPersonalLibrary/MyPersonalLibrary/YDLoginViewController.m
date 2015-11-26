//
//  YDLoginViewController.m
//  MyPersonalLibrary
//
//  Created by sijiewang on 11/26/15.
//  Copyright © 2015 lnmcc. All rights reserved.
//

#import "YDLoginViewController.h"

@interface YDLoginViewController ()

@end

@implementation YDLoginViewController

@synthesize delegate;

- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil {
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        
    }
    return self;
}

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view from its nib.
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

/*
#pragma mark - Navigation

// In a storyboard-based application, you will often want to do a little preparation before navigation
- (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender {
    // Get the new view controller using [segue destinationViewController].
    // Pass the selected object to the new view controller.
}
*/

- (IBAction)loginUser:(UIButton *)sender {
    if (([self.nameField.text length] == 0) || ([self.passwordField.text length] == 0)) {
        [self showErrorWithMessage: @"Both fields are mandatory"];
    } else {
        KeychainItemWrapper *keychain = [[KeychainItemWrapper alloc] initWithIdentifier:@"YDAPPNAME" accessGroup:nil];
        if ([self.nameField.text isEqualToString:[keychain objectForKey:(__bridge id)kSecAttrAccount]]) {
            if ([[self.passwordField.text MD5] isEqualToString: [keychain objectForKey:(__bridge id)kSecValueData]]) {
                [self.delegate loginWithSuccess];
            } else {
                [self showErrorWithMessage: @"Password not correct."];
            }
        } else {
            [self showErrorWithMessage: @"Name not correct."];
        }
    }
}

- (IBAction)cancelLogin:(UIButton *)sender {
    [self.delegate loginCancelled];
}

- (void)showErrorWithMessage: (NSString *)msg {
    UIAlertView *alert = [[UIAlertView alloc] initWithTitle:@"Error" message:msg delegate:self cancelButtonTitle:@"OK" otherButtonTitles:nil, nil];
    [alert show];
}

@end



















