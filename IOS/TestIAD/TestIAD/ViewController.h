//
//  ViewController.h
//  TestIAD
//
//  Created by sijiewang on 7/12/15.
//  Copyright (c) 2015 lnmcc. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <iAd/iAd.h>

#define S_WIDTH 1024
#define S_HEIGHT 768

@interface ViewController : UIViewController <UIScrollViewDelegate, ADInterstitialAdDelegate>

@property (weak, nonatomic) IBOutlet UIScrollView *scrollView;
@property (weak, nonatomic) IBOutlet UIPageControl *pageControl;

@end

