//
//  YDConfigurationHelper.h
//  MyPersonalLibrary
//
//  Created by sijiewang on 11/26/15.
//  Copyright © 2015 lnmcc. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface YDConfigurationHelper : NSObject

+ (void)setApplicationStartupDefaults;
+ (BOOL)getBoolValueForConfigurationKey: (NSString *)_objectkey;
+ (NSString *)getStringValueForConfiguationKey: (NSString *)_objectkey;
+ (void)setBoolValueForConfigurationKey:(NSString *)_objectkey withValue:(BOOL)_boolvalue;
+ (void)setStringValueForConfigurationKey:(NSString *)_objectkey withValue:(NSString *)_value;

@end
