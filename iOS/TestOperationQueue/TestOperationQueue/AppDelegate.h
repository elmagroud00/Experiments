//
//  AppDelegate.h
//  TestOperationQueue
//
//  Created by sijiewang on 1/18/16.
//  Copyright © 2016 lnmcc. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <Foundation/Foundation.h>

@interface AppDelegate : UIResponder <UIApplicationDelegate> {
    NSOperationQueue *queue;
}

@property (strong, nonatomic) UIWindow *window;

+ (instancetype) shared;
- (void) pageLoaded:(NSXML) document;

@end

