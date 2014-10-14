//
//  main.m
//  BasicStringOperation
//
//  Created by sijiewang on 10/11/14.
//  Copyright (c) 2014 lnmcc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <Foundation/NSObject.h>

int main(int argc, const char * argv[]) {
    @autoreleasepool {
        NSString *str1 = @"This is string A";
        NSString *str2 = @"This is string B";
        NSString *res;
        NSRange subRange;
        res = [str1 substringToIndex: 3];
        NSLog(@"First 3 chars of str1: %@", res);
        
        res = [str1 substringFromIndex: 5];
        NSLog(@"Chars from index 5 of str1: %@", res);
        
        res = [[str1 substringFromIndex: 8] substringToIndex: 6];
        NSLog(@"Chars from index 8 through 13: %@", res);
        
        res = [str1 substringWithRange: NSMakeRange(8, 6)];
        NSLog(@"Chars from index 8 through 13: %@", res);
    }
    return 0;
}
