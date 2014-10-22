//
//  AppDelegate.h
//  SpeakLine
//
//  Created by sijiewang on 10/22/14.
//  Copyright (c) 2014 lnmcc. All rights reserved.
//

#import <Cocoa/Cocoa.h>

@interface AppDelegate : NSObject <NSApplicationDelegate>
{
    NSSpeechSynthesizer *_speechSynth;
}

- (IBAction)stopIt:(id)sender;
- (IBAction)sayIt:(id)sender;
@property (weak) IBOutlet NSTextField *textField;

@end

