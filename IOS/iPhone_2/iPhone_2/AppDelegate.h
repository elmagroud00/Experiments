//
//  AppDelegate.h
//  iPhone_2
//
//  Created by sijiewang on 10/29/14.
//  Copyright (c) 2014 lnmcc. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface AppDelegate : UIResponder <UIApplicationDelegate> {
    UILabel *display;
}
@property (strong, nonatomic) UIWindow *window;
@property(nonatomic, retain)IBOutlet UILabel *display;
-(IBAction)click:(id)sender;

@end