//
//  main.m
//  TestObjcCopy
//
//  Created by sijiewang on 10/18/14.
//  Copyright (c) 2014 lnmcc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <Foundation/NSObject.h>
#import <Foundation/NSArray.h>
#import <Foundation/NSAutoreleasePool.h>

int main(int argc, const char * argv[]) {

    NSAutoreleasePool *pool = [[NSAutoreleasePool alloc]init];
    NSMutableArray *dataArray = [NSMutableArray arrayWithObjects:
                                 [NSMutableString stringWithString:@"one"],
                                 [NSMutableString stringWithString: @"two"],
                                 [NSMutableString stringWithString: @"three"],
                                 nil];
    NSMutableArray *dataArray2;
    NSMutableString *mStr;
    
    NSLog(@"dataArray: ");
    for(NSString *elem in dataArray) {
        NSLog(@"%@", elem);
    }
    
    dataArray2 = [dataArray mutableCopy];
    mStr = [dataArray objectAtIndex: 0];
    [mStr appendString: @"ONE"];
    NSLog(@"dataArray: ");
    for(NSString *elem in dataArray) {
        NSLog(@"%@", elem);
    }
    
    NSLog(@"dataArray2: ");
    for(NSString *elem in dataArray2) {
        NSLog(@"%@", elem);
    }
    
    [dataArray2 release];
    [pool drain];
    
    return 0;
}
