//
//  DetailViewController.m
//  TreeNavigation
//
//  Created by sijiewang on 6/6/15.
//  Copyright (c) 2015 lnmcc. All rights reserved.
//

#import "DetailViewController.h"

@interface DetailViewController ()

@end

@implementation DetailViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view.
    self.web.scalesPageToFit = YES;
    
    //[self loadWebPageWithString:@"www.lnmcc.net"];
    //NSURLRequest *request=[NSURLRequest requestWithURL:[NSURL URLWithString:@"http://www.baidu.com"]];
    //[self.web loadRequest:request];
}

- (void)viewDidAppear:(BOOL)animated {
    //[self loadWebPageWithString: self.url];
}

- (void)loadWebPageWithString:(NSString*)urlString {
    NSURL *url = [NSURL URLWithString:urlString];
    NSURLRequest *request = [NSURLRequest requestWithURL:url];
    NSLog(@"url = %@", urlString);
    [self.web loadRequest:request];
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
