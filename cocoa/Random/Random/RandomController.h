//
//  RandomController.h
//  Random
//
//  Created by sijiewang on 10/19/14.
//  Copyright (c) 2014 lnmcc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <AppKit/AppKit.h>

@interface RandomController : NSObject {
    IBOutlet NSTextField *textField;
}
-(IBAction)seed:(id)sender;
-(IBAction)generate:(id)sender;
@end
