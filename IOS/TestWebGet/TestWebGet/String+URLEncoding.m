//
//  String+URLEncoding.m
//  TestWebGet
//
//  Created by sijiewang on 7/4/15.
//  Copyright (c) 2015 lnmcc. All rights reserved.
//

#import "String+URLEncoding.h"
#import <CoreFoundation/CoreFoundation.h>

@implementation NSString (URLEncoding)

-(NSString*)URLEncodedString {
    CFStringRef StringRef = CFURLCreateStringByAddingPercentEscapes(kCFAllocatorDefault, (CFStringRef)self, NULL, CFSTR("+$,#[] "), kCFStringEncodingUTF8);
    NSString *result = (NSString*)CFBridgingRelease(StringRef);
    return result;
}

-(NSString*)URLDecodedString {
    CFStringRef stringRef = CFURLCreateStringByReplacingPercentEscapesUsingEncoding(kCFAllocatorDefault, (CFStringRef)self, CFSTR(""), kCFStringEncodingUTF8);
    
    NSString *result = (NSString*)CFBridgingRelease(stringRef);
    return  result;
}

@end
