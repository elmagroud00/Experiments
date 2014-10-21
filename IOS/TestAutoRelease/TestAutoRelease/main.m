//
//  main.m
//  TestAutoRelease
//
//  Created by sijiewang on 10/17/14.
//  Copyright (c) 2014 lnmcc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <Foundation/NSObject.h>

@interface Foo : NSObject
{
    int x;
}
@end

@implementation Foo
@end

int main(int argc, const char * argv[]) {

    NSAutoreleasePool *pool = [[NSAutoreleasePool alloc]init];
    Foo *myFoo = [[Foo alloc]init];
    NSLog(@"myFoo retain count = %lu", (unsigned long)[myFoo retainCount]);
    [pool drain];
    pool = [[NSAutoreleasePool alloc]init];
    [myFoo autorelease];
    NSLog(@"myFoo retain count = %lu", (unsigned long)[myFoo retainCount]);
    [myFoo retain];
    NSLog(@"myFoo retain count = %lu", (unsigned long)[myFoo retainCount]);
    [pool drain];
    NSLog(@"myFoo retain count = %lu", (unsigned long)[myFoo retainCount]);
    [myFoo release];
    
    return 0;
}
