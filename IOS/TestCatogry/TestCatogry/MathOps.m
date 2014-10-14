//
//  MathOps.m
//  TestCatogry
//
//  Created by sijiewang on 9/21/14.
//  Copyright (c) 2014 lnmcc. All rights reserved.
//

#import "MathOps.h"

@implementation Fraction (MathOps)
-(Fraction*) add:(Fraction *)f
{
    Fraction *result = [[Fraction alloc]init];
    int resultNum, resultDenom;
    resultNum = (numerator * f->denominator) + (denominator * f->numerator);
    resultDenom = denominator * f->denominator;
    [result setTo:resultNum over:resultDenom];
    return result;
}

@end
