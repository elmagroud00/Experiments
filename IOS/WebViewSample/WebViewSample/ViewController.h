//
//  ViewController.h
//  WebViewSample
//
//  Created by sijiewang on 5/21/15.
//  Copyright (c) 2015 lnmcc. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface ViewController : UIViewController

@property (weak, nonatomic) IBOutlet UIWebView *webView;

- (IBAction)testLoadHTMLString:(UIButton *)sender;
- (IBAction)testLoadData:(UIButton *)sender;
- (IBAction)testLoadRequest:(UIButton *)sender;

@end

