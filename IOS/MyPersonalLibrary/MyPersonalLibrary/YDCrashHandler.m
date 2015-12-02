//
//  YDCrashHandler.m
//  MyPersonalLibrary
//
//  Created by sijiewang on 11/28/15.
//  Copyright © 2015 lnmcc. All rights reserved.
//

#import "YDCrashHandler.h"
#include <libkern/OSAtomic.h>
#include <execinfo.h>

NSString * const YDCrashHandlerSignalExceptionName =
@"YDCrashHandlerSignalExceptionName";
NSString * const YDCrashHandlerSignalKey =
@"YDCrashHandlerSignalKey";
NSString * const YDCrashHandlerAddressedKey =
@"YDCrashHandlerAddressesKey";

volatile int32_t UncaughtExceptionCount = 0;
const int32_t UncaughtExceptionMaximum = 10;

const NSInteger UncaughtExceptionHandlerSkipAddressCount = 4;
const NSInteger UncaughtExceptionReportAddressCount = 5;


@implementation YDCrashHandler

+ (NSArray *)backtrace {
    void *callstack[128];
    int frames = backtrace(callstack, 128);
    char **strs = backtrace_symbols(callstack, frames);
    
    int i;
    NSMutableArray *backtrace = [NSMutableArray arrayWithCapacity:frames];
    for (i = UncaughtExceptionHandlerSkipAddressCount;
         i < UncaughtExceptionHandlerSkipAddressCount +
         UncaughtExceptionReportAddressCount;
         i++) {
        [backtrace addObject:[NSString stringWithUTF8String:strs[i]]];
        
    }
    free(strs);
    return backtrace;
}

- (void)alertView:(UIAlertView *)anAlertView clickedButtonAtIndex:(NSInteger)buttonIndex {
    dismissed = YES;
}

- (void)handleException:(NSException *)exception {
    UIAlertView *thisAlert = [[UIAlertView alloc] initWithTitle:
                              @"Sorry" message:@"An unexceptioned envent happened causing the application to shutdown." delegate:nil cancelButtonTitle:@"OK" otherButtonTitles:nil, nil];
    [thisAlert show];
    
    CFRunLoopRef runLoop = CFRunLoopGetCurrent();
    CFArrayRef allModes = CFRunLoopCopyAllModes(runLoop);
    
    while (!dismissed) {
        for (NSString *mode in (NSArray *)CFBridgingRelease(allModes)) {
            CFRunLoopRunInMode((CFStringRef) CFBridgingRetain(mode), 0.001, false);
        }
    }
    CFRelease(allModes);
    
    NSSetUncaughtExceptionHandler(NULL);
    signal(SIGABRT, SIG_DFL);
    signal(SIGILL, SIG_DFL);
    signal(SIGSEGV, SIG_DFL);
    signal(SIGFPE, SIG_DFL);
    signal(SIGBUS, SIG_DFL);
    signal(SIGPIPE, SIG_DFL);
    
    if ([[exception name] isEqual: YDCrashHandlerSignalExceptionName]) {
        kill(getpid(), [[[exception userInfo]objectForKey:YDCrashHandlerSignalKey] intValue]);
    } else {
        [exception raise];
    }
}

@end

void HandleException(NSException *exception) {
    int32_t exceptionCount = OSAtomicIncrement32(&UncaughtExceptionCount);
    if (exceptionCount > UncaughtExceptionMaximum) {
        return;
    }
    NSArray *callStack = [YDCrashHandler backtrace];
    NSMutableDictionary *userInfo = [NSMutableDictionary dictionaryWithDictionary:[exception userInfo]];
    [userInfo setObject:callStack forKey:YDCrashHandlerAddressedKey];
    
    [[[YDCrashHandler alloc] init] performSelectorOnMainThread:@selector(handleException:) withObject:[NSException exceptionWithName:[exception name] reason:[exception reason] userInfo:userInfo] waitUntilDone:YES];
}

void SignalHandler(int signal) {
    int32_t exceptionCount = OSAtomicIncrement32(&UncaughtExceptionCount);
    if (exceptionCount > UncaughtExceptionMaximum) {
        return;
    }
    NSMutableDictionary *userInfo = [NSMutableDictionary dictionaryWithObject:[NSNumber numberWithInt:signal] forKey:YDCrashHandlerSignalKey];
    NSArray *callStack = [YDCrashHandler backtrace];
    [userInfo setObject:callStack forKey:YDCrashHandlerAddressedKey];
    
    [[[YDCrashHandler alloc] init] performSelectorOnMainThread:@selector(handleException:) withObject:[NSException exceptionWithName:YDCrashHandlerSignalExceptionName reason:[NSString stringWithFormat:@"Signal %d was raised.", signal] userInfo:[NSDictionary dictionaryWithObject:[NSNumber numberWithInt:signal] forKey:YDCrashHandlerSignalKey]] waitUntilDone:YES];
}

void InstallCrashExceptionHandler() {
    NSSetUncaughtExceptionHandler(&HandleException);
    signal(SIGABRT, SignalHandler);
    signal(SIGILL, SignalHandler);
    signal(SIGSEGV, SignalHandler);
    signal(SIGFPE, SignalHandler);
    signal(SIGBUS, SignalHandler);
    signal(SIGPIPE, SignalHandler);
    
}

























