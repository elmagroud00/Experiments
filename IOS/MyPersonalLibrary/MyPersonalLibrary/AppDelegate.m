//
//  AppDelegate.m
//  MyPersonalLibrary
//
//  Created by sijiewang on 11/26/15.
//  Copyright © 2015 lnmcc. All rights reserved.
//

#import "AppDelegate.h"
#import "YDCrashHandler.h"
#import "YDViewController.h"

@interface AppDelegate ()

@end

@implementation AppDelegate


- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {
    // Override point for customization after application launch.
    
    if (bYDInstallCrashHandler) {
        [self performSelector:@selector(installYDCrashHandler) withObject:nil afterDelay:0];
    }
    
    if (![YDConfigurationHelper getBoolValueForConfigurationKey:bYDFirstLaunch]) {
        [YDConfigurationHelper setApplicationStartupDefaults];
    }
    
    if (bYDActivateGPSOnStartUp) {
        //
    }
    
    if (bYDRegistrationRequested && ![YDConfigurationHelper getBoolValueForConfigurationKey:bYDRegistered]) {
        self.registrationVC = [[YDRegistrationViewController alloc] init];
        self.registrationVC.delegate = self;
        self.window = [[UIWindow alloc] initWithFrame:[[UIScreen mainScreen] bounds]];
        self.window.rootViewController = _registrationVC;
        self.window.backgroundColor = [UIColor clearColor];
        [self.window makeKeyAndVisible];
    } else {
        if (bYDLoginRequired) {
            self.loginVC = [[YDLoginViewController alloc] init];
            self.loginVC.delegate = self;
            self.window = [[UIWindow alloc] initWithFrame:[[UIScreen mainScreen] bounds]];
            self.window.rootViewController = _loginVC;
            self.window.backgroundColor = [UIColor clearColor];
            [self.window makeKeyAndVisible];
        } else {
            self.viewController = [[YDViewController alloc] init];
            self.window.rootViewController = self.viewController;
            [self.window makeKeyAndVisible];
        }
    }
    
    return YES;
}

#pragma Registration Delegates
- (void)registeredWithError {
    
}

- (void)registeredWithSuccess {
    if (bYDShowLoginAfterRegistration) {
        self.loginVC = [[YDLoginViewController alloc] init];
        self.loginVC.delegate = self;
        self.window = [[UIWindow alloc] initWithFrame:[[UIScreen mainScreen] bounds]];
        self.window.rootViewController = self.loginVC;
        self.window.backgroundColor = [UIColor clearColor];
        [self.window makeKeyAndVisible];
    } else {
        self.viewController = [[YDViewController alloc] init];
        self.window.rootViewController = self.viewController;
        [self.window makeKeyAndVisible];
    }
}

- (void)cancelRegistration {
    
}

#pragma Login delegates
- (void)loginWithSuccess {
    self.viewController = [[YDViewController alloc] init];
    self.window.rootViewController = self.viewController;
    [self.window makeKeyAndVisible];
}

- (void)loginWithError {
    
}

- (void)loginCancelled {
    
}

- (void)applicationWillResignActive:(UIApplication *)application {
    // Sent when the application is about to move from active to inactive state. This can occur for certain types of temporary interruptions (such as an incoming phone call or SMS message) or when the user quits the application and it begins the transition to the background state.
    // Use this method to pause ongoing tasks, disable timers, and throttle down OpenGL ES frame rates. Games should use this method to pause the game.
}

- (void)applicationDidEnterBackground:(UIApplication *)application {
    // Use this method to release shared resources, save user data, invalidate timers, and store enough application state information to restore your application to its current state in case it is terminated later.
    // If your application supports background execution, this method is called instead of applicationWillTerminate: when the user quits.
}

- (void)applicationWillEnterForeground:(UIApplication *)application {
    // Called as part of the transition from the background to the inactive state; here you can undo many of the changes made on entering the background.
}

- (void)applicationDidBecomeActive:(UIApplication *)application {
    // Restart any tasks that were paused (or not yet started) while the application was inactive. If the application was previously in the background, optionally refresh the user interface.
}

- (void)applicationWillTerminate:(UIApplication *)application {
    // Called when the application is about to terminate. Save data if appropriate. See also applicationDidEnterBackground:.
}

- (void)installYDCrashHandler {
    InstallCrashExceptionHandler();
}

@end















