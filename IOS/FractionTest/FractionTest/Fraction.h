//
//  Fraction.h
//  FractionTest
//
//  Created by sijiewang on 9/7/14.
//  Copyright (c) 2014 lnmcc. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface Fraction : NSObject
{
    int numberator;
    int denominator;
}
-(void) print;
-(void) setNumberator: (int) n;
-(void) setDenominator: (int) d;
-(int) numberator;
-(int) denominator;
-(double) convertToNum;
@end
