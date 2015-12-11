//
//  YDViewController.m
//  WebsiteUsingBlock
//
//  Created by sijiewang on 12/11/15.
//  Copyright © 2015 lnmcc. All rights reserved.
//

#import "YDViewController.h"
#import "URLRequest.h"

@interface YDViewController ()

@end

@implementation YDViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    NSURL *myURL = [NSURL URLWithString:@"http://lnmcc.net/wordpress/wp-content/uploads/2014/04/DSCF2801.jpg"];
    NSMutableURLRequest *request = [NSMutableURLRequest requestWithURL:myURL cachePolicy:NSURLRequestReloadIgnoringLocalCacheData timeoutInterval:60];
    URLRequest *urlRequest = [[URLRequest alloc] initWithRequest:request];
    [urlRequest startWithCompletion:^(URLRequest *request, NSData *data, BOOL success) {
        if (success) {
            self.logoImage.image = [UIImage imageWithData:data];
        } else {
            NSLog(@"error %@", [[NSString alloc] initWithData:data encoding:NSUTF8StringEncoding]);
        }
    }];
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
