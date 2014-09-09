//
//  Fraction.m
//  Fraction2
//
//  Created by sijiewang on 9/9/14.
//  Copyright (c) 2014 lnmcc. All rights reserved.
//

#import "Fraction.h"

@implementation Fraction
@synthesize numerator, denominator;
-(void) print
{
    NSLog(@"%i / %i", numerator, denominator);
}
-(double) convertToNum
{
    if(denominator != 0)
        return (double)numerator / denominator;
    else
        return 0;
}
-(void) setTo: (int) n over:(int) d
{
    numerator = n;
    denominator = d;
}
@end
