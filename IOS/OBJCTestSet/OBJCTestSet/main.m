//
//  main.m
//  OBJCTestSet
//
//  Created by sijiewang on 10/12/14.
//  Copyright (c) 2014 lnmcc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <Foundation/NSObject.h>
#import <Foundation/NSSet.h>
#import <Foundation/NSValue.h>
#import <Foundation/NSString.h>

#define INTOBJ(v) [NSNumber numberWithInteger : v]

@interface NSSet(Printing)
-(void) print;
@end

@implementation NSSet(Printing)
-(void) print
{
    printf("\n");
    for(NSNumber *element in self)
        printf("%li", (long)[element integerValue]);
    printf("\n");
}
@end

int main(int argc, const char * argv[]) {
    @autoreleasepool {
        NSMutableSet *set1 = [NSMutableSet setWithObjects:
                              INTOBJ(1), INTOBJ(2), INTOBJ(3), nil];
        NSSet *set2 = [NSSet setWithObjects:
                       INTOBJ(-5), INTOBJ(100), INTOBJ(3), nil];
        NSSet *set3 = [NSSet setWithObjects:
                       INTOBJ(12), INTOBJ(200), INTOBJ(3), INTOBJ(9), nil];
        NSLog(@"Set1:");
        [set1 print];
        NSLog(@"Set2:");
        [set2 print];
        NSLog(@"Set3:");
        [set3 print];
    }
    return 0;
}
