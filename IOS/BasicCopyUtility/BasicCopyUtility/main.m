//
//  main.m
//  BasicCopyUtility
//
//  Created by sijiewang on 10/13/14.
//  Copyright (c) 2014 lnmcc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <Foundation/NSString.h>
#import <Foundation/NSArray.h>
#import <Foundation/NSFileManager.h>
#import <Foundation/NSPathUtilities.h>
#import <Foundation/NSProcessInfo.h>

int main(int argc, const char * argv[]) {
    @autoreleasepool {
        NSFileManager *fm;
        NSString *source, *dest;
        BOOL isDir;
        NSProcessInfo *proc = [NSProcessInfo processInfo];
        NSArray *args = [proc arguments];
        fm = [NSFileManager defaultManager];
        if([args count] != 3) {
            NSLog(@"Usage: %@ src dest", [proc processName]);
            return 1;
        }
        source = [args objectAtIndex: 1];
        dest = [args objectAtIndex: 2];
        if([fm isReadableFileAtPath: source] == NO) {
            NSLog(@"Cant read %@", source);
            return 2;
        }
        [fm fileExistsAtPath: dest isDirectory: &isDir];
        if(isDir == YES)
            dest = [dest stringByAppendingPathComponent:[source lastPathComponent]];
        [fm removeFileAtPath: dest handler: nil];
        if([fm copyPath: source toPath: dest handler:nil] == NO) {
            NSLog(@"Copy failed!");
            return 3;
        }
        NSLog(@"Copy of %@ to %@ succeeded!", source, dest);
    }
    return 0;
}
