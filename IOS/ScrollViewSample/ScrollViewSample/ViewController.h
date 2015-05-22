//
//  ViewController.h
//  ScrollViewSample
//
//  Created by sijiewang on 5/21/15.
//  Copyright (c) 2015 lnmcc. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface ViewController : UIViewController {
    BOOL keyboardVisible;
}

@property (weak, nonatomic) IBOutlet UIScrollView *scrollView;
@property (weak, nonatomic) IBOutlet UITextField *textField;

@end

