//
//  ViewController.h
//  TextKit_Sample
//
//  Created by sijiewang on 6/10/15.
//  Copyright (c) 2015 lnmcc. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface ViewController : UIViewController

@property (nonatomic, strong) NSTextContainer *textContainer;
@property (strong, nonatomic) IBOutlet UITextView *textView;

- (void) markWord:(NSString*)word inTextStorage:(NSTextStorage*)textStorage;
@end

