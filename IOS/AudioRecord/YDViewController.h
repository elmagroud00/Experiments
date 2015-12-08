//
//  YDViewController.h
//  AudioRecord
//
//  Created by sijiewang on 12/8/15.
//  Copyright © 2015 lnmcc. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <AVFoundation/AVFoundation.h>

@interface YDViewController : UIViewController
@property (weak, nonatomic) IBOutlet UIButton *recordButton;
@property (weak, nonatomic) IBOutlet UIButton *playButton;
@property (weak, nonatomic) IBOutlet UIButton *stopButton;
@property (strong, nonatomic) AVAudioRecorder *audioRecoder;
@property (strong, nonatomic) AVAudioPlayer *audioPlayer;
@end
