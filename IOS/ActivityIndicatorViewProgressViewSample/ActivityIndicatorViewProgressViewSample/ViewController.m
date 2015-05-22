//
//  ViewController.m
//  ActivityIndicatorViewProgressViewSample
//
//  Created by sijiewang on 5/22/15.
//  Copyright (c) 2015 lnmcc. All rights reserved.
//

#import "ViewController.h"

@interface ViewController ()

@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view, typically from a nib.
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (IBAction)startToMove:(UIButton *)sender {
    if ([self.myActivityIndicatorView isAnimating]) {
        [self.myActivityIndicatorView stopAnimating];
    } else {
        [self.myActivityIndicatorView startAnimating];
    }
}

- (IBAction)downloadProgress:(UIButton *)sender {
    myTimer = [NSTimer scheduledTimerWithTimeInterval:1.0 target:self selector:@selector(download) userInfo:nil repeats:YES];
}

- (void)download {
    self.myProgressView.progress = self.myProgressView.progress + 0.1;
    if (self.myProgressView.progress == 1.0) {
        [myTimer invalidate];
        UIAlertView *alert = [[UIAlertView alloc] initWithTitle:@"download completed!" message:@"" delegate:nil cancelButtonTitle:@"OK" otherButtonTitles:nil, nil];
        [alert show];
    }
}
@end
