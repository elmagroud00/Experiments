//
//  AppDelegate.h
//  SpeakLine
//
//  Created by sijiewang on 10/22/14.
//  Copyright (c) 2014 lnmcc. All rights reserved.
//

#import <Cocoa/Cocoa.h>

@interface AppDelegate : NSObject <NSApplicationDelegate, NSSpeechSynthesizerDelegate, NSTableViewDataSource, NSTableViewDelegate>
{
    NSArray *_voices;
    NSSpeechSynthesizer *_speechSynth;
}

- (IBAction)stopIt:(id)sender;
- (IBAction)sayIt:(id)sender;
@property (weak) IBOutlet NSTextField *textField;
@property (weak) IBOutlet NSButton *stopButton;
@property (weak) IBOutlet NSButton *speakButton;
@property (weak) IBOutlet NSTableView *tableView;

@end

