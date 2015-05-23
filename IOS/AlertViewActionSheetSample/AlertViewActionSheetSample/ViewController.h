//
//  ViewController.h
//  AlertViewActionSheetSample
//
//  Created by sijiewang on 5/22/15.
//  Copyright (c) 2015 lnmcc. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface ViewController : UIViewController <UIAlertViewDelegate, UIActionSheetDelegate>

- (IBAction)testAlertView:(UIButton *)sender;
- (IBAction)testAlertSheet:(UIButton *)sender;

@end

