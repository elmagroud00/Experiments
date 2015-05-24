//
//  ViewController.h
//  ToolbarSample
//
//  Created by sijiewang on 5/23/15.
//  Copyright (c) 2015 lnmcc. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface ViewController : UIViewController

@property (weak, nonatomic) IBOutlet UILabel *label;

- (IBAction)Save:(UIBarButtonItem *)sender;

- (IBAction)Open:(UIBarButtonItem *)sender;

@end

