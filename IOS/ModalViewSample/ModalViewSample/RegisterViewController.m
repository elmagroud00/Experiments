//
//  RegisterViewController.m
//  ModalViewSample
//
//  Created by sijiewang on 6/3/15.
//  Copyright (c) 2015 lnmcc. All rights reserved.
//

#import "RegisterViewController.h"

@interface RegisterViewController ()

@end

@implementation RegisterViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view.
    
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (void)textFieldDidEndEditing:(UITextField *)textField {
    
}

- (IBAction)done:(id)sender {
    [self dismissViewControllerAnimated:YES completion:^{
        NSLog(@"Modal View done");
        NSDictionary *dataDict = [NSDictionary dictionaryWithObject:self.txtUsername.text forKey:@"username"];
        [[NSNotificationCenter defaultCenter]postNotificationName:@"RegisterCompletionNotification" object:nil userInfo:dataDict];
    }];
}



/*
#pragma mark - Navigation

// In a storyboard-based application, you will often want to do a little preparation before navigation
- (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender {
    // Get the new view controller using [segue destinationViewController].
    // Pass the selected object to the new view controller.
}
*/

@end
