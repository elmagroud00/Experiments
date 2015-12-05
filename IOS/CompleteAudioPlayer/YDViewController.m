//
//  YDViewController.m
//  CompleteAudioPlayer
//
//  Created by sijiewang on 12/5/15.
//  Copyright © 2015 lnmcc. All rights reserved.
//

#import "YDViewController.h"

@interface YDViewController ()

- (IBAction)trackSliderMoved:(UISlider *)sender;
- (IBAction)volumeSliderMoved:(UISlider *)sender;
- (IBAction)playOrPause:(UIBarButtonItem *)sender;

@end

@implementation YDViewController

- (void)viewDidLoad {
    NSLog(@"ViewDidLoad at YDViewController()");
    [super viewDidLoad];
    NSURL *fileURL = [[NSURL alloc] initWithString:[[NSBundle mainBundle] pathForResource:@"miss_dong" ofType:@"mp3"]];
    self.player = [[AVAudioPlayer alloc] initWithContentsOfURL:fileURL error:nil];
    if (self.player) {
        [self updateViewForPlayerInfo: self.player];
        [self updateViewForPlayerState: self.player];
        [self.player prepareToPlay];
        self.player.delegate = self;
    }
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    
}

#pragma mark AVAudioPlayer Delegate
- (void)audioPlayerDidFinishPlaying:(AVAudioPlayer *)player successfully:(BOOL)flag {
    [self.updateTimer invalidate];
    self.updateTimer = nil;
}

/*
#pragma mark - Navigation

// In a storyboard-based application, you will often want to do a little preparation before navigation
- (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender {
    // Get the new view controller using [segue destinationViewController].
    // Pass the selected object to the new view controller.
}
*/

- (void)updateCurrentTime {
    [self updateCurrentTimeForPlayer:self.player];
}

- (void)updateViewForPlayerInfo: (AVAudioPlayer *)p {
    self.trackStatus.text = [NSString stringWithFormat:@"%d:%02d", (int)p.duration / 60, (int)p.duration % 60, nil];
    self.trackSlider.maximumValue = p.duration;
    self.volumeSlider.value = p.volume;
}

- (void)updateCurrentTimeForPlayer: (AVAudioPlayer *)p {
    self.trackStatus.text = [NSString stringWithFormat:@"%d:%02d", (int)p.currentTime / 60, (int)p.currentTime % 60, nil];
    self.trackSlider.value = p.currentTime;
}

- (void)updateViewForPlayerState: (AVAudioPlayer *)p {
    [self updateCurrentTimeForPlayer: p];
    if (self.updateTimer != nil) {
        [self.updateTimer invalidate];
    }
    if (p.playing) {
        self.updateTimer = [NSTimer scheduledTimerWithTimeInterval:.01 target:self selector:@selector(updateCurrentTime) userInfo:p repeats:YES];
    } else {
        self.updateTimer = nil;
    }
}

- (IBAction)trackSliderMoved:(UISlider *)sender {
    self.player.currentTime = sender.value;
    [self updateCurrentTimeForPlayer: self.player];
}

- (IBAction)volumeSliderMoved:(UISlider *)sender {
    self.player.volume = [sender value];
}

- (IBAction)playOrPause:(UIBarButtonItem *)sender {
    if (self.player) {
        if (self.player.playing) {
            [self.player pause];
            [self.playButton setTitle:@"Play"];
            [self updateViewForPlayerState: self.player];
        } else {
            [self.player play];
            [self.playButton setTitle:@"Pause"];
            [self updateViewForPlayerState: self.player];
        }
    }
}
@end















