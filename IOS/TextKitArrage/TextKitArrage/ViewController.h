//
//  ViewController.h
//  TextKitArrage
//
//  Created by sijiewang on 6/10/15.
//  Copyright (c) 2015 lnmcc. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface ViewController : UIViewController
@property (nonatomic, strong) NSTextContainer *textContainer;
@property (nonatomic, strong) IBOutlet UITextView *textView;
@property (weak, nonatomic) IBOutlet UIImageView *imageView;

- (void) markWord:(NSString*)word inTextStorage:(NSTextStorage*)textStorage;

@end

