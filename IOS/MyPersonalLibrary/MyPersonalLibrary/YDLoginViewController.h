//
//  YDLoginViewController.h
//  MyPersonalLibrary
//
//  Created by sijiewang on 11/26/15.
//  Copyright © 2015 lnmcc. All rights reserved.
//

#import <UIKit/UIKit.h>

@protocol YDLoginViewControllerDelegate <NSObject>

- (void)loginWithSuccess;
- (void)loginWithError;
- (void)loginCancelled;

@end

@interface YDLoginViewController : UIViewController

@property (nonatomic, assign) id<YDLoginViewControllerDelegate> delegate;

@property (weak, nonatomic) IBOutlet UITextField *nameField;
@property (weak, nonatomic) IBOutlet UITextField *passwordField;

- (IBAction)loginUser:(UIButton *)sender;
- (IBAction)cancelLogin:(UIButton *)sender;

@end
