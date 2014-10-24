//
//  AppDelegate.m
//  SpeakLine
//
//  Created by sijiewang on 10/22/14.
//  Copyright (c) 2014 lnmcc. All rights reserved.
//

#import "AppDelegate.h"

@interface AppDelegate ()

@property (weak) IBOutlet NSWindow *window;

@end

@implementation AppDelegate

@synthesize window = _window;
@synthesize textField = _textField;
@synthesize tableView = _tableView;

-(id)init {
    self = [super init];
    if(self) {
        NSLog(@"init");
        _speechSynth = [[NSSpeechSynthesizer alloc] initWithVoice:nil];
        [_speechSynth setDelegate:self];
        _voices = [NSSpeechSynthesizer availableVoices];
    }
    return self;
}

-(void)awakeFromNib {
    NSString *defaultVoice = [NSSpeechSynthesizer defaultVoice];
    NSInteger defaultRow = [_voices indexOfObject:defaultVoice];
    NSIndexSet *indices = [NSIndexSet indexSetWithIndex:defaultRow];
    [_tableView selectRowIndexes:indices byExtendingSelection:NO];
    [_tableView scrollRowToVisible:defaultRow];
}

-(void)tableViewSelectionDidChange:(NSNotification *)notification {
    NSInteger row = [_tableView selectedRow];
    if(row == -1)
        return;
    
    NSString *selectedVoice = [_voices objectAtIndex:row];
    [_speechSynth setVoice:selectedVoice];
    NSLog(@"new voice = %@", selectedVoice);
}

-(NSInteger)numberOfRowsInTableView:(NSTableView *)tableView {
    return (NSInteger)[_voices count];
}

-(id)tableView:(NSTableView *)tableView objectValueForTableColumn:(NSTableColumn *)tableColumn row:(NSInteger)row {
    NSString *v = [_voices objectAtIndex:row];
    NSDictionary *dict = [NSSpeechSynthesizer attributesForVoice:v];
    return [dict objectForKey:NSVoiceName];
}

-(void)speechSynthesizer:(NSSpeechSynthesizer *)sender didFinishSpeaking:(BOOL)finishedSpeaking {
    NSLog(@"finished Speaking = %d", finishedSpeaking);
    [_stopButton setEnabled:NO];
    [_speakButton setEnabled:YES];
    [_tableView setEnabled:YES];
}

- (void)applicationDidFinishLaunching:(NSNotification *)aNotification {
    // Insert code here to initialize your application
}

- (void)applicationWillTerminate:(NSNotification *)aNotification {
    // Insert code here to tear down your application
}

- (IBAction)stopIt:(id)sender {
    NSLog(@"stopping");
    [_speechSynth stopSpeaking];
    [_tableView setEnabled:YES];
}

- (IBAction)sayIt:(id)sender {
    NSString *string = [_textField stringValue];
    if([string length] == 0) {
        NSLog(@"string from %@ is of size zero-length", _textField);
        return;
    }
    [_speechSynth startSpeakingString:string];
    NSLog(@"Have started to say: %@", string);
    
    [_stopButton setEnabled:YES];
    [_speakButton setEnabled:NO];
    [_tableView setEnabled:NO];
}
@end
