//
//  YDViewController.m
//  AudioRecord
//
//  Created by sijiewang on 12/8/15.
//  Copyright © 2015 lnmcc. All rights reserved.
//

#import "YDViewController.h"

@interface YDViewController () <AVAudioRecorderDelegate, AVAudioPlayerDelegate>
- (IBAction)startRecording:(UIButton *)sender;
- (IBAction)startPlaying:(UIButton *)sender;
- (IBAction)stopRecording:(UIButton *)sender;
@end

@implementation YDViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    [self.stopButton setHidden:YES];
    [self.playButton setHidden:YES];
}

- (NSURL *)soundFileURL {
    NSArray *dirPaths;
    NSString *docsDir;
    
    dirPaths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES);
    docsDir = [dirPaths objectAtIndex:0];
    NSString *soundFilePath = [docsDir stringByAppendingPathComponent:@"recording.m4a"];
    return [NSURL fileURLWithPath:soundFilePath];
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

/*
 #pragma mark - Navigation
 
 // In a storyboard-based application, you will often want to do a little preparation before navigation
 - (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender {
 // Get the new view controller using [segue destinationViewController].
 // Pass the selected object to the new view controller.
 }
 */

- (IBAction)startRecording:(UIButton *)sender {
    [self.recordButton setHidden:YES];
    [self.stopButton setHidden:NO];
    [self.playButton setHidden:YES];
    
    NSError *error = nil;
    AVAudioSession *session = [AVAudioSession sharedInstance];
    [session setCategory:AVAudioSessionCategoryRecord error:nil];
    [session setActive:YES error:&error];
    if (error) {
        NSLog(@"AVAudioSession Error: %@", [error localizedDescription]);
    }
    
    NSMutableDictionary *recordSetting = [[NSMutableDictionary alloc] init];
    [recordSetting setValue:[NSNumber numberWithInt:kAudioFormatMPEG4AAC] forKey:AVFormatIDKey];
    [recordSetting setValue:[NSNumber numberWithFloat:44100.0] forKey:AVSampleRateKey];
    [recordSetting setValue:[NSNumber numberWithInt:2] forKey:AVNumberOfChannelsKey];
    [recordSetting setValue:[NSNumber numberWithInt:16] forKey:AVLinearPCMBitDepthKey];
    [recordSetting setValue:[NSNumber numberWithBool:NO] forKey:AVLinearPCMIsBigEndianKey];
    [recordSetting setValue:[NSNumber numberWithBool:NO] forKey:AVLinearPCMIsFloatKey];
    
    self.audioRecoder = [[AVAudioRecorder alloc] initWithURL:[self soundFileURL] settings:recordSetting error:&error];
    self.audioRecoder.delegate = self;
    if (error) {
        NSLog(@"error: %@", [error localizedDescription]);
    } else {
        [self.audioRecoder prepareToRecord];
    }
    if (!self.audioRecoder.recording) {
        self.recordButton.enabled = NO;
        self.stopButton.enabled = YES;
        [self.audioRecoder record];
    }
}

- (IBAction)startPlaying:(UIButton *)sender {
    NSLog(@"Start playing ... ...");
    NSError *error = nil;
    AVAudioSession *session = [AVAudioSession sharedInstance];
    [session setCategory:AVAudioSessionCategoryPlayback error:nil];
    [session setActive:YES error:&error];
    if (error) {
        NSLog(@"AVAudioSession Error: %@", [error localizedDescription]);
    }
    
    [self.playButton setUserInteractionEnabled:NO];
    NSURL *url = [self soundFileURL];
    self.audioPlayer = [[AVAudioPlayer alloc] initWithContentsOfURL:url error:&error];
    if (error) {
        NSLog(@"Error in audioPlayer: %@", [error localizedDescription]);
    } else {
        self.audioPlayer.delegate = self;
        [self.audioPlayer prepareToPlay];
        [self.audioPlayer play];
    }
}

- (IBAction)stopRecording:(UIButton *)sender {
    [self.stopButton setHidden:YES];
    [self.recordButton setHidden:NO];
    self.recordButton.enabled = YES;
    self.stopButton.enabled = NO;
    [self.audioRecoder stop];
    self.audioRecoder = nil;
    [self.playButton setHidden:NO];
}

#pragma delegates
- (void)audioPlayerDidFinishPlaying:(AVAudioPlayer *)player successfully:(BOOL)flag {
    self.audioPlayer = nil;
    [self.playButton setUserInteractionEnabled:YES];
}

- (void)audioRecorderDidFinishRecording:(AVAudioRecorder *)recorder successfully:(BOOL)flag {
    UIAlertView *alert = [[UIAlertView alloc] initWithTitle:@"Thanks" message:@"Your recording has finished" delegate:self cancelButtonTitle:@"OK" otherButtonTitles:nil, nil];
    [alert show];
}

- (void)audioRecorderEncodeErrorDidOccur:(AVAudioRecorder *)recorder error:(NSError *)error {
    UIAlertView *alert = [[UIAlertView alloc] initWithTitle:@"Error" message:@"An error has occured" delegate:self cancelButtonTitle:@"OK" otherButtonTitles:nil, nil];
    [alert show];
}
@end

















