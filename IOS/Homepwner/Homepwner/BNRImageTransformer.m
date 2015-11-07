//
//  BNRImageTransformer.m
//  Homepwner
//
//  Created by sijiewang on 11/7/15.
//  Copyright © 2015 lnmcc. All rights reserved.
//

#import "BNRImageTransformer.h"
#import <UIKit/UIKit.h>

@implementation BNRImageTransformer

+ (Class)transformedValueClass {
    return [NSData class];
}

- (id) transformedValue:(id)value {
    if (!value) {
        return nil;
    }
    if ([value isKindOfClass:[NSData class]]) {
        return value;
    }
    
    return UIImagePNGRepresentation(value);
}

- (id) reverseTransformedValue:(id)value {
    return [UIImage imageWithData:value];
}

@end
