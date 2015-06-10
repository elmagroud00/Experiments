//
//  DetailViewController.h
//  TreeNavigation
//
//  Created by sijiewang on 6/6/15.
//  Copyright (c) 2015 lnmcc. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface DetailViewController : UIViewController
@property (strong, nonatomic) NSString *url;
@property (weak, nonatomic) IBOutlet UIWebView *web;

- (void)loadWebPageWithString:(NSString*)urlString;
@end
