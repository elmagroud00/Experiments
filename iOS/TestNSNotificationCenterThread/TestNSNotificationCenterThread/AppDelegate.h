//
//  AppDelegate.h
//  TestNSNotificationCenterThread
//
//  Created by sijiewang on 3/2/16.
//  Copyright © 2016 lnmcc. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "MyObserver.h"

@interface AppDelegate : UIResponder <UIApplicationDelegate> {
    MyObserver *myObserver;
}

@property (strong, nonatomic) UIWindow *window;


@end

