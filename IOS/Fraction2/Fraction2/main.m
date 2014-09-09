//
//  main.m
//  Fraction2
//
//  Created by sijiewang on 9/9/14.
//  Copyright (c) 2014 lnmcc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "Fraction.h"
int main(int argc, const char * argv[])
{

    @autoreleasepool {
        Fraction *aFraction = [[Fraction alloc]init];
        [aFraction setTo:100 over:200];
        [aFraction print];
        
        Fraction *bFraction = [[Fraction alloc]init];
        [bFraction setTo:1 over:2];
        [bFraction print];

        [
    }
    return 0;
}

