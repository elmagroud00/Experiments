//
//  AddViewController.h
//  TestWebGet
//
//  Created by sijiewang on 7/5/15.
//  Copyright (c) 2015 lnmcc. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "String+URLEncoding.h"

@interface AddViewController : UIViewController <UITextViewDelegate, NSURLConnectionDelegate, NSURLConnectionDataDelegate>

@property (weak, nonatomic) IBOutlet UITextView *textView;

- (IBAction)onClickDone:(id)sender;
- (IBAction)onClickSava:(id)sender;

@property (strong, nonatomic) NSMutableData *datas;

- (void)startRequest;

@end
