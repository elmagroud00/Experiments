//
//  main.m
//  Fraction
//
//  Created by sijiewang on 9/3/14.
//  Copyright (c) 2014 lnmcc. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface Fraction: NSObject
{
    int numberator;
    int denominator;
}
- (void) print;
- (void) setNumberator: (int) n;
- (void) setDenominator: (int) d;
@end

@implementation Fraction
- (void) print
{
    NSLog(@"%i/%i", numberator, denominator);
}
- (void) setNumberator:(int)n
{
    numberator = n;
}
-(void) setDenominator:(int)d
{
    denominator = d;
}
@end

int main(int argc, const char * argv[])
{

    @autoreleasepool {
        Fraction* myFractor;
        myFractor = [Fraction alloc];
        myFractor = [myFractor init];
        [myFractor setNumberator:1];
        [myFractor setDenominator:3];
        [myFractor print];
    }
    return 0;
}

