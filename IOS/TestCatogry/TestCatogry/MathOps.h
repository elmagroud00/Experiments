//
//  MathOps.h
//  TestCatogry
//
//  Created by sijiewang on 9/21/14.
//  Copyright (c) 2014 lnmcc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "Fraction.h"

@interface Fraction (MathOps)
-(Fraction*) add: (Fraction*)f;
-(Fraction*) mul: (Fraction*)f;
-(Fraction*) sub: (Fraction*)f;
-(Fraction*) div: (Fraction*)f;
@end
