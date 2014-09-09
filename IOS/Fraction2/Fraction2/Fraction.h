//
//  Fraction.h
//  Fraction2
//
//  Created by sijiewang on 9/9/14.
//  Copyright (c) 2014 lnmcc. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface Fraction : NSObject
{
    int numerator;
    int denominator;
}
@property int numerator, denominator;
-(void) print;
-(void) setTo: (int)n over: (int) d;
-(double) convertToNum;
-(void) add: (Fraction*)f;
@end
