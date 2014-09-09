//
//  main.m
//  Calculator
//
//  Created by sijiewang on 9/7/14.
//  Copyright (c) 2014 lnmcc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <ctype.h>

@interface Calculator : NSObject
{
    double accumulator;
}

-(void) setAccumulator: (double) value;
-(void) clear;
-(double) acculumator;
-(void) add: (double) value;
-(void) subtract: (double) value;
-(void) multiply: (double) value;
-(void) divide: (double) value;
@end

@implementation Calculator

-(void) setAccumulator: (double) value
{
    accumulator = value;
}

-(void) clear
{
    accumulator = 0;
}

-(double) acculumator
{
    return accumulator;
}

-(void) add:(double)value
{
    accumulator += value;
}

-(void) subtract:(double)value
{
    accumulator -= value;
}

-(void) multiply:(double)value
{
    accumulator *= value;
}

-(void) divide:(double)value
{
    accumulator /= value;
}

@end


int main(int argc, const char * argv[])
{

    @autoreleasepool {
        double value1, value2;
        char operator;
        Calculator *deskCalc = [[Calculator alloc] init];
        NSLog(@"Type in your expression.");
        scanf("%lf %c %lf", &value1, &operator, &value2);
        [deskCalc setAccumulator:value1];
        if(operator == '+')
            [deskCalc add:value2];
        else if(operator == '-')
            [deskCalc subtract:value2];
        else if(operator == '*')
            [deskCalc multiply:value2];
        else if(operator == '/')
            [deskCalc divide:value2];
        NSLog(@"%.2f", [deskCalc acculumator]);
    }
    return 0;
}

