//
//  RegisterViewController.h
//  ModalViewSample
//
//  Created by sijiewang on 6/3/15.
//  Copyright (c) 2015 lnmcc. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface RegisterViewController : UIViewController <UITextFieldDelegate>

@property (weak, nonatomic) IBOutlet UITextField *txtUsername;
- (IBAction)done:(id)sender;

@end
