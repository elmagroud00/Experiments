//
//  ViewController.m
//  TestIAD
//
//  Created by sijiewang on 7/12/15.
//  Copyright (c) 2015 lnmcc. All rights reserved.
//

#import "ViewController.h"

@interface ViewController ()

@property (strong, nonatomic) NSMutableArray *pageList;
@property (strong, nonatomic) ADInterstitialAd *interstital;

@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view, typically from a nib.
    self.interstital = [[ADInterstitialAd alloc]init];
    self.interstital.delegate = self;
    self.scrollView.delegate = self;
    
    self.pageList = [[NSMutableArray alloc]init];
    [self.pageList addObject:[[UIImageView alloc] initWithImage:[UIImage imageNamed:@"apple-1.jpg"]]];
    [self.pageList addObject:[[UIImageView alloc]
                              initWithImage:[UIImage imageNamed:@"apple-2.jpg"]]];
    [self.pageList addObject:[[UIImageView alloc]
                              initWithImage:[UIImage imageNamed:@"apple-3.jpg"]]];
    [self reloadPage];
}

- (void)reloadPage {
    int contentHeight = self.scrollView.frame.size.height;
    self.pageControl.numberOfPages = [self.pageList count];
    self.scrollView.contentSize = CGSizeMake([self.pageList count] * S_WIDTH, contentHeight);
    
    for (int i = 0 ; i < [self.pageList count]; ++i) {
        UIView *view = self.pageList[i];
        [view removeFromSuperview];
        view.frame = CGRectMake(S_WIDTH * i, 0.0f, S_WIDTH, contentHeight);
        [self.scrollView addSubview:view];
    }
}

- (void)interstitialAdDidLoad:(ADInterstitialAd *)interstitialAd {
    NSLog(@"广告加载成功");
    UIView *intersitialContainer = [[UIView alloc] initWithFrame:CGRectZero];
    [self.pageList insertObject:intersitialContainer atIndex:self.pageControl.currentPage];
    [self reloadPage];
    [self.interstital presentInView:intersitialContainer];
}

- (void)interstitialAdDidUnload:(ADInterstitialAd *)interstitialAd {
    NSLog(@"广告卸载");
    for (UIView *item in self.pageList) {
        if ([item isMemberOfClass:[UIView class]]) {
            [item removeFromSuperview];
            [self.pageList removeObject:item];
            [self reloadPage];
            break;
        }
    }
}

- (void)interstitialAdActionDidFinish:(ADInterstitialAd *)interstitialAd {
    NSLog(@"广告关闭");
}

- (BOOL)interstitialAdActionShouldBegin:(ADInterstitialAd *)interstitialAd willLeaveApplication:(BOOL)willLeave {
    return YES;
}

- (void)interstitialAd:(ADInterstitialAd *)interstitialAd didFailWithError:(NSError *)error {
    NSLog(@"广告加载失败");
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}



@end
