//
//  Fraction.m
//  FractionTest
//
//  Created by sijiewang on 9/7/14.
//  Copyright (c) 2014 lnmcc. All rights reserved.
//

#import "Fraction.h"

@implementation Fraction
-(void) print
{
    NSLog(@"%i/%i", numberator, denominator);
}
-(void) setNumberator:(int)n
{
    numberator = n;
}
-(void) setDenominator:(int)d
{
    denominator = d;
}
-(int) numberator
{
    return numberator;
}
-(int) denominator
{
    return denominator;
}
-(double) convertToNum
{
    if(denominator != 0)
        return (double)numberator / denominator;
    else
        return 1.0;
}
@end
