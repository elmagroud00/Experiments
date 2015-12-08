//
//  YDViewController.h
//  VideoPlayer
//
//  Created by sijiewang on 12/8/15.
//  Copyright © 2015 lnmcc. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <MediaPlayer/MediaPlayer.h>

@interface YDViewController : UIViewController
@property (weak, nonatomic) IBOutlet UIButton *moviePlayButton;
@property (nonatomic, strong) MPMoviePlayerController *moviePlayerView;
@end
