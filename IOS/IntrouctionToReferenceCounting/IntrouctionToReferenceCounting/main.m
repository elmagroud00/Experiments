//
//  main.m
//  IntrouctionToReferenceCounting
//
//  Created by sijiewang on 10/17/14.
//  Copyright (c) 2014 lnmcc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <Foundation/NSObject.h>
#import <Foundation/NSAutoreleasePool.h>
#import <Foundation/NSString.h>
#import <Foundation/NSArray.h>

@interface ClassA : NSObject
{
    NSString *str;
}
-(void)setStr:(NSString*)s;
-(NSString*)str;
-(void)dealloc;
@end

@implementation ClassA
-(void)setStr:(NSString *)s
{
    [str autorelease];
    str = [s retain];
}

-(NSString*)str
{
    return str;
}

-(void)dealloc
{
    NSLog(@"ClassA dealloc");
    [str release];
    [super dealloc];
}
@end

int main(int argc, const char * argv[]) {

    NSAutoreleasePool *pool = [[NSAutoreleasePool alloc]init];
    NSString *myStr = [NSMutableString stringWithString:@"A string"];
    ClassA *myA = [[ClassA alloc]init];
    NSLog(@"myStr retain count: %x", [myStr retainCount]);
    [myA autorelease];
    [myA setStr:myStr];
    NSLog(@"myStr retain count: %x", [myStr retainCount]);
    [pool drain];
    
    return 0;
}
