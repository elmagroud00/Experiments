//
//  main.m
//  FractionTest
//
//  Created by sijiewang on 9/7/14.
//  Copyright (c) 2014 lnmcc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "Fraction.h"

int main(int argc, const char * argv[])
{

    @autoreleasepool {
        Fraction *myFraction = [[Fraction alloc]init];
        [myFraction setNumberator: 1];
        [myFraction setDenominator: 3];
        NSLog(@"The value of myFraction is: ");
        [myFraction print];
    }
    return 0;
}

