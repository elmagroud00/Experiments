//
//  AppDelegate.h
//  KVCFun
//
//  Created by sijiewang on 10/24/14.
//  Copyright (c) 2014 lnmcc. All rights reserved.
//

#import <Cocoa/Cocoa.h>

@interface AppDelegate : NSObject <NSApplicationDelegate>
{
    int fido;
}
@property (readwrite, assign)int fido;

-(int)fido;

@end

