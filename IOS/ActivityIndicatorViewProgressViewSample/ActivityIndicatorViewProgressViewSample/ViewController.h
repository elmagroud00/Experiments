//
//  ViewController.h
//  ActivityIndicatorViewProgressViewSample
//
//  Created by sijiewang on 5/22/15.
//  Copyright (c) 2015 lnmcc. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface ViewController : UIViewController {
    NSTimer *myTimer;
}

@property (weak, nonatomic) IBOutlet UIActivityIndicatorView *myActivityIndicatorView;
@property (weak, nonatomic) IBOutlet UIProgressView *myProgressView;

- (IBAction)startToMove:(UIButton *)sender;
- (IBAction)downloadProgress:(UIButton *)sender;


@end

