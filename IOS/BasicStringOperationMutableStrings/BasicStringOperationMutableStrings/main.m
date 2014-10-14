//
//  main.m
//  BasicStringOperationMutableStrings
//
//  Created by sijiewang on 10/12/14.
//  Copyright (c) 2014 lnmcc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <Foundation/NSObject.h>
#import <Foundation/NSString.h>
int main(int argc, const char * argv[]) {
    @autoreleasepool {
        NSString *str1 = @"This is string A";
        NSString *search, *relpace;
        NSMutableString *mstr;
        NSRange substr;
        
        mstr = [NSMutableString stringWithString: str1];
        NSLog(@"%@", mstr);
        
        [mstr insertString: @"mutable" atIndex: 8];
        NSLog(@"%@", mstr);
    }
    return 0;
}
