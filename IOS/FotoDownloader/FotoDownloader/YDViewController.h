//
//  YDViewController.h
//  FotoDownloader
//
//  Created by sijiewang on 12/9/15.
//  Copyright © 2015 lnmcc. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface YDViewController : UIViewController
@property (weak, nonatomic) IBOutlet UILabel *statusLabel;
@property (weak, nonatomic) IBOutlet UIProgressView *progressView;
@property (weak, nonatomic) IBOutlet UIImageView *receivedImage;
@property (nonatomic, retain, readwrite) NSOutputStream *fileStream;
@property (nonatomic, assign, readonly) BOOL isReceiving;
@property (nonatomic, retain, readwrite) NSURLConnection *connection;
@property (nonatomic, copy, readwrite) NSString *filePath;
@end
