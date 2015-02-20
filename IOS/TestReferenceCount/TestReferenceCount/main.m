//
//  main.m
//  TestReferenceCount
//
//  Created by sijiewang on 10/17/14.
//  Copyright (c) 2014 lnmcc. All rights reserved.
//
#import <Foundation/Foundation.h>
#import <Foundation/NSAutoreleasePool.h>
#import <Foundation/NSString.h>
#import <Foundation/NSObject.h>
@interface ClassA : NSObject {
    NSString *str;
}
-(void)setStr:(NSString*)s;
-(NSString*)str;
@end
@implementation ClassA
-(void)setStr:(NSString*)s
{
    str = s;
    [str retain];
}
-(NSString*)str
{
    return str;
}
@end
int main(int argc, const char * argv[]) {
    NSAutoreleasePool *pool = [[NSAutoreleasePool alloc]init];
    NSMutableString *myStr = [NSMutableString stringWithString:@"A String"];
    ClassA *myA = [[ClassA alloc]init];
    NSLog(@"myStr retain count: %x", [myStr retainCount]);
    [myA setStr:myStr];
    NSLog(@"myStr retain count: %x", [myStr retainCount]);
    [myStr release];
    NSLog(@"myStr retain count: %x", [myStr retainCount]);
    [myA release];
    [pool drain];
    return 0;
}
