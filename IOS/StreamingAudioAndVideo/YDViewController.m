//
//  YDViewController.m
//  StreamingAudioAndVideo
//
//  Created by sijiewang on 12/5/15.
//  Copyright © 2015 lnmcc. All rights reserved.
//

#import "YDViewController.h"
#import <MediaPlayer/MediaPlayer.h>

@interface YDViewController ()

@property (nonatomic, strong) MPMoviePlayerController *moviePlayerController;

@end

@implementation YDViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view from its nib.
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

- (IBAction)playStream:(UIButton *)sender {
    NSURL *streamURL = [NSURL URLWithString:@"http://devimages.apple.com/iphone/samples/bipbop/bipbopall.m3u8"];
    self.moviePlayerController = [[MPMoviePlayerController alloc] initWithContentURL:streamURL];
    [self.moviePlayerController prepareToPlay];
    [self.moviePlayerController play];
}
@end
