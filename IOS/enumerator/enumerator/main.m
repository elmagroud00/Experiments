//
//  main.m
//  enumerator
//
//  Created by sijiewang on 10/13/14.
//  Copyright (c) 2014 lnmcc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <Foundation/NSString.h>
#import <Foundation/NSFileManager.h>
#import <Foundation/NSArray.h>

int main(int argc, const char * argv[]) {
    @autoreleasepool {
        NSString *path;
        NSFileManager *fm;
        NSDirectoryEnumerator *dirEnum;
        NSArray *dirArray;
        
        fm = [NSFileManager defaultManager];
        path = [fm currentDirectoryPath];
        dirEnum = [fm enumeratorAtPath:path];
        NSLog(@"Contents of %@", path);
        while((path = [dirEnum nextObject]) != nil)
            NSLog(@"%@", path);
        
        dirArray = [fm directoryContentsAtPath: [fm currentDirectoryPath]];
        NSLog(@"Contents using directoryContentsAtPath: ");
        for(path in dirArray)
            NSLog(@"%@", path);
    }
    return 0;
}
