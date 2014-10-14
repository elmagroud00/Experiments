//
//  Fraction.m
//  TestCatogry
//
//  Created by sijiewang on 9/21/14.
//  Copyright (c) 2014 lnmcc. All rights reserved.
//

#import "Fraction.h"

@implementation Fraction
-(void) setTo:(int)n over:(int)d
{
    numerator = n;
    denominator = d;
}
-(void) print
{
    NSLog(@"%d / %d", numerator, denominator);
}
@end
