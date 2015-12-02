//
//  YDCrashHandler.h
//  MyPersonalLibrary
//
//  Created by sijiewang on 11/28/15.
//  Copyright © 2015 lnmcc. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface YDCrashHandler : NSObject {

    BOOL dismissed;

}

void InstallCrashExceptionHandler();

@end
