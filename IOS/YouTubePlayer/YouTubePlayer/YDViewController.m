//
//  YDViewController.m
//  YouTubePlayer
//
//  Created by sijiewang on 12/8/15.
//  Copyright © 2015 lnmcc. All rights reserved.
//

#import "YDViewController.h"

@interface YDViewController ()
@property (weak, nonatomic) IBOutlet UIWebView *youtubeViewer;
@end

@implementation YDViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    NSString *embedHTML = @"\
    <html><head>\
    <style type=\"text/css\">\
    body {\
    background-color: transparent;\
    color: white;\
    }\
    </style>\
    </head><body style=\"margin:0\">\
    <iframe title=\"YouTube Video\" class=\"youtube-player\" type=\"text/html\"\ width=\"320\" height=\"460\" src=\"%@\"\
    frameborder=\"0\" allowFullScreen ></iframe>";
    NSString *urlToOpen = @"https://www.youtube.com/embed/u1zgFlCw8Aw?autoplay=1";
    NSString *html = [NSString stringWithFormat:embedHTML, urlToOpen];
    [self.youtubeViewer loadHTMLString:html baseURL:nil];
    
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

@end
