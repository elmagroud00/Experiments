//
//  main.m
//  TestCatogry
//
//  Created by sijiewang on 9/21/14.
//  Copyright (c) 2014 lnmcc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "Fraction.h"
#import "MathOps.h"

int main(int argc, const char * argv[]) {
    @autoreleasepool {
        Fraction *a = [[Fraction alloc] init];
        Fraction *b = [[Fraction alloc]init];
        Fraction *result;
        [a setTo:1 over:2];
        [a print];
        [b setTo:1 over:3];
        [b print];
        result = [a add: b];
        [result print];
    }
    return 0;
}
