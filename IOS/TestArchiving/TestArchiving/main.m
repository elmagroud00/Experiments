//
//  main.m
//  TestArchiving
//
//  Created by sijiewang on 10/29/14.
//  Copyright (c) 2014 lnmcc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <Foundation/NSObject.h>
#import <Foundation/NSString.h>
#import <Foundation/NSKeyedArchiver.h>

@interface Foo : NSObject<NSCoding>
{
    NSString *strVal;
    int intVal;
    float floatVal;
}
@property(copy, nonatomic)NSString *strVal;
@property int intVal;
@property float floatVal;

@end

@implementation Foo
@synthesize strVal, intVal, floatVal;

-(void)encodeWithCoder:(NSCoder *)encoder {
    [encoder encodeObject:strVal forKey:@"FoostrVal"];
    [encoder encodeInt:intVal forKey:@"FoointVal"];
    [encoder encodeFloat:floatVal forKey:@"FoofloatVal"];
}

-(id)initWithCoder:(NSCoder *)decoder {
    strVal = [decoder decodeObjectForKey:@"FoostrVal"];
    intVal = [decoder decodeIntForKey:@"FoointVal"];
    floatVal = [decoder decodeFloatForKey:@"FoofloatVal"];
    return self;
}


@end

int main(int argc, const char * argv[]) {
    @autoreleasepool {
        Foo *myFoo1 = [[Foo alloc]init];
        Foo *myFoo2;
        [myFoo1 setStrVal:@"This is the string"];
        [myFoo1 setIntVal:12345];
        [myFoo1 setFloatVal:98.6];
        [NSKeyedArchiver archiveRootObject:myFoo1 toFile:@"foo.arch"];
        myFoo2 = [NSKeyedUnarchiver unarchiveObjectWithFile:@"foo.arch"];
        NSLog(@"%@ %i %g\n", [myFoo2 strVal], [myFoo2 intVal], [myFoo2 floatVal]);
    }
    return 0;
}
