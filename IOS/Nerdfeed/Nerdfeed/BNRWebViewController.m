//
//  BNRWebViewController.m
//  Nerdfeed
//
//  Created by sijiewang on 10/13/15.
//  Copyright © 2015 lnmcc. All rights reserved.
//

#import "BNRWebViewController.h"

@interface BNRWebViewController ()
@end

@implementation BNRWebViewController

- (void)viewDidLoad {
    //[super viewDidLoad];
    UIWebView *webView = [[UIWebView alloc] init];
    webView.scalesPageToFit = YES;
    self.view = webView;
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (void)setURL:(NSURL *)URL {
    _URL = URL;
    if (_URL) {
        NSURLRequest *req = [NSURLRequest requestWithURL:_URL];
        [(UIWebView *)self.view loadRequest:req];
    }
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
