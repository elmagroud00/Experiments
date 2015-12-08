//
//  YDViewController.m
//  VideoPlayer
//
//  Created by sijiewang on 12/8/15.
//  Copyright © 2015 lnmcc. All rights reserved.
//

#import "YDViewController.h"

@interface YDViewController ()
- (IBAction)playVideo:(UIButton *)sender;
@end

@implementation YDViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    self.view.backgroundColor = [UIColor whiteColor];
    NSString *path = [[NSBundle mainBundle] pathForResource:@"Movie" ofType:@"m4v"];
    NSLog(@"File Path: %@", path);
    NSURL *url = [NSURL fileURLWithPath:path];
    NSLog(@"File URL: %@", url);
    
    self.moviePlayerView = [[MPMoviePlayerController alloc] initWithContentURL:url];
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(thumbnailReady:) name:MPMoviePlayerThumbnailImageRequestDidFinishNotification object:nil];
    NSMutableArray *timeArr = [[NSMutableArray alloc] init];
    [timeArr addObject:[NSNumber numberWithFloat:5.f]];
    [self.moviePlayerView requestThumbnailImagesAtTimes:timeArr timeOption:MPMovieTimeOptionNearestKeyFrame];
}

- (void)thumbnailReady:(NSNotification *)notification {
    NSDictionary *userInfo = [notification userInfo];
    UIImage *image = [userInfo objectForKey:@"MPMoviePlayerThumbnailImageKey"];
    [self.moviePlayButton setBackgroundImage:image forState:UIControlStateNormal];
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

- (IBAction)playVideo:(UIButton *)sender {
    [self presentMoviePlayerViewControllerAnimated:self.moviePlayerView];
    self.moviePlayerView.movieSourceType = MPMovieSourceTypeFile;
    [self.moviePlayerView play];
}
@end







