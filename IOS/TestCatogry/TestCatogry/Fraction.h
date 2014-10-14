//
//  Fraction.h
//  TestCatogry
//
//  Created by sijiewang on 9/21/14.
//  Copyright (c) 2014 lnmcc. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface Fraction : NSObject
{
    int numerator;
    int denominator;
}
@property int numerator, denominator;
-(void) setTo: (int)n over: (int)d;
-(void) print;
@end
