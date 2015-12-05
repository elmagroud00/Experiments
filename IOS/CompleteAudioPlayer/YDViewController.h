//
//  YDViewController.h
//  CompleteAudioPlayer
//
//  Created by sijiewang on 12/5/15.
//  Copyright © 2015 lnmcc. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <AVFoundation/AVFoundation.h>

@interface YDViewController : UIViewController <AVAudioPlayerDelegate>
@property (weak, nonatomic) IBOutlet UILabel *trackStatus;
@property (weak, nonatomic) IBOutlet UISlider *trackSlider;
@property (weak, nonatomic) IBOutlet UISlider *volumeSlider;
@property (weak, nonatomic) IBOutlet UIBarButtonItem *playButton;
@property (nonatomic, retain) AVAudioPlayer *player;
@property (nonatomic, strong) NSTimer *updateTimer;
@end
