//
//  AppDelegate.m
//  KVCFun
//
//  Created by sijiewang on 10/24/14.
//  Copyright (c) 2014 lnmcc. All rights reserved.
//

#import "AppDelegate.h"
#import <Foundation/NSNumberFormatter.h>

@interface AppDelegate ()

@property (weak) IBOutlet NSWindow *window;
@end

@implementation AppDelegate

@synthesize fido;

- (void)applicationDidFinishLaunching:(NSNotification *)aNotification {
    // Insert code here to initialize your application
}

- (void)applicationWillTerminate:(NSNotification *)aNotification {
    // Insert code here to tear down your application
}

-(id)init {
    self = [super init];
    if(self) {
        [self setValue:[NSNumber numberWithInt:5] forKey:@"fido"];
        NSNumber *n = [self valueForKey:@"fido"];
        NSLog(@"fido = %@", n);
    }
    return self;
}

-(IBAction)incrementFido:(id)sender {
    [self willChangeValueForKey:@"fido"];
    fido++;
    NSLog(@"fido is now %d", fido);
    [self didChangeValueForKey:@"fido"];
}

@end
