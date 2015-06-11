//
//  ViewController.m
//  TextKitArrage
//
//  Created by sijiewang on 6/10/15.
//  Copyright (c) 2015 lnmcc. All rights reserved.
//

#import "ViewController.h"

@interface ViewController ()

@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view, typically from a nib.
    CGRect textViewRect = CGRectInset(self.view.bounds, 200, 200);
    NSTextStorage *textStorage = [[NSTextStorage alloc] initWithString:_textView.text];
    NSLayoutManager *layoutManager = [[NSLayoutManager alloc]init];
    [textStorage addLayoutManager:layoutManager];
    _textContainer = [[NSTextContainer alloc]initWithSize:textViewRect.size];
    [layoutManager addTextContainer:_textContainer];
    
    [_textView removeFromSuperview];
    _textView = [[UITextView alloc] initWithFrame:textViewRect textContainer:_textContainer];
    
    [self.view insertSubview:_textView belowSubview:_imageView];
    
    [textStorage beginEditing];
    NSDictionary *attrsDic = @{NSTextEffectAttributeName:NSTextEffectLetterpressStyle};
    NSMutableAttributedString *attrStr = [[NSMutableAttributedString alloc] initWithString:_textView.text attributes:attrsDic];
    [textStorage setAttributedString:attrStr];
    [self markWord:@"我" inTextStorage:textStorage];
    [textStorage endEditing];
    _textView.textContainer.exclusionPaths = @[[self translatedBezierPath]];
    
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(preferredContentSizeChanged:) name:UIContentSizeCategoryDidChangeNotification object:nil];
}

- (void)preferredContentSizeChanged: (NSNotification*) notification {
    self.textView.font = [UIFont preferredFontForTextStyle:UIFontTextStyleBody];
}

- (UIBezierPath*) translatedBezierPath {
    CGRect imageRect = [self.textView convertRect:_imageView.frame fromView:self.view];
    UIBezierPath *newPath = [UIBezierPath bezierPathWithRect:imageRect];
    return newPath;
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (void) markWord:(NSString *)word inTextStorage:(NSTextStorage *)textStorage {
    NSRegularExpression *regex = [NSRegularExpression regularExpressionWithPattern:word options:0 error:nil];
    NSArray *matches = [regex matchesInString:_textView.text options:0 range:NSMakeRange(0, [_textView.text length])];
    for (NSTextCheckingResult *match in matches) {
        NSRange matchRange = [match range];
        [textStorage addAttribute:NSForegroundColorAttributeName value:[UIColor redColor] range:matchRange];
    }
}

@end
