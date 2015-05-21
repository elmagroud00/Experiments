//
//  ViewController.m
//  Switch_Slider_SegmentedControlSample
//
//  Created by sijiewang on 5/21/15.
//  Copyright (c) 2015 lnmcc. All rights reserved.
//

#import "ViewController.h"

@interface ViewController ()

@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view, typically from a nib.
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (IBAction)touchDown:(UISegmentedControl *)sender {
    if(_LeftSwitch.hidden == YES) {
        self.RightSwitch.hidden = NO;
        self.LeftSwitch.hidden = NO;
    } else {
        self.RightSwitch.hidden = YES;
        self.LeftSwitch.hidden = YES;
    }
}

- (IBAction)sliderValueChange:(UISlider *)sender {
    UISlider *slider = sender;
    float progressAsFloat = slider.value;
    NSString *newText = [[NSString alloc]initWithFormat:@"%0.1f", progressAsFloat];
    self.SliderValue.text = newText;
}

- (IBAction)valueChanged:(UISwitch *)sender {
    UISwitch *witchSwitch = (UISwitch*)sender;
    BOOL settings = witchSwitch.isOn;
    [self.LeftSwitch setOn:settings animated:YES];
    [self.RightSwitch setOn:settings animated:YES];
}

@end
