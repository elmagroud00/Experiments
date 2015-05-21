//
//  ViewController.h
//  Switch_Slider_SegmentedControlSample
//
//  Created by sijiewang on 5/21/15.
//  Copyright (c) 2015 lnmcc. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface ViewController : UIViewController

@property (weak, nonatomic) IBOutlet UILabel *SliderValue;
@property (weak, nonatomic) IBOutlet UISwitch *LeftSwitch;
@property (weak, nonatomic) IBOutlet UISwitch *RightSwitch;

- (IBAction)touchDown:(UISegmentedControl *)sender;
- (IBAction)sliderValueChange:(UISlider *)sender;
- (IBAction)valueChanged:(UISwitch *)sender;
@end

