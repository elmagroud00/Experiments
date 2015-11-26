//
//  YDConfigurationHelper.m
//  MyPersonalLibrary
//
//  Created by sijiewang on 11/26/15.
//  Copyright © 2015 lnmcc. All rights reserved.
//

#import "YDConfigurationHelper.h"
//#import "YDConstants.h"

@implementation YDConfigurationHelper

+ (void)setApplicationStartupDefaults {
    NSUserDefaults *defaults = [NSUserDefaults standardUserDefaults];
    [defaults synchronize];
    [defaults setBool:NO forKey:bYDFirstLaunch];
    [defaults setBool:NO forKey:bYDAuthenticated];
    [defaults synchronize];
}

+ (BOOL)getBoolValueForConfigurationKey:(NSString *)_objectkey {
    NSUserDefaults *defaults = [NSUserDefaults standardUserDefaults];
    [defaults synchronize];
    return [defaults boolForKey:_objectkey];
}

+ (NSString *)getStringValueForConfiguationKey:(NSString *)_objectkey {
    NSUserDefaults *defaults = [NSUserDefaults standardUserDefaults];
    [defaults synchronize];
    if ([defaults stringForKey:_objectkey] == nil) {
        return @"";
    } else {
        return [defaults stringForKey:_objectkey];
    }
}

+ (void)setBoolValueForConfigurationKey:(NSString *)_objectkey withValue:(BOOL)_boolvalue {
    NSUserDefaults *defaults = [NSUserDefaults standardUserDefaults];
    [defaults synchronize];
    [defaults setBool:_boolvalue forKey:_objectkey];
    [defaults synchronize];
}

+ (void)setStringValueForConfigurationKey:(NSString *)_objectkey withValue:(NSString *)_value {
    NSUserDefaults *defaults = [NSUserDefaults standardUserDefaults];
    [defaults synchronize];
    [defaults setObject:_value forKey:_objectkey];
    [defaults synchronize];
}

@end
