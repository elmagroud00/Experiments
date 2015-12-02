//
//  AppDelegate.h
//  MyPersonalLibrary
//
//  Created by sijiewang on 11/26/15.
//  Copyright © 2015 lnmcc. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "YDRegistrationViewController.h"
#import "YDLoginViewController.h"

@interface AppDelegate : UIResponder <UIApplicationDelegate, YDLoginViewControllerDelegate, YDRegistrationViewControllerDelegate>

@property (strong, nonatomic) UIWindow *window;
@property (strong, nonatomic) YDViewController *viewController;
@property (strong, nonatomic) YDLoginViewController *loginVC;
@property (strong, nonatomic) YDRegistrationViewController *registrationVC;


@end

