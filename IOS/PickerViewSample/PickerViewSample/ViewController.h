//
//  ViewController.h
//  PickerViewSample
//
//  Created by sijiewang on 5/23/15.
//  Copyright (c) 2015 lnmcc. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface ViewController : UIViewController <UIPickerViewDelegate, UIPickerViewDataSource>

@property (weak, nonatomic) IBOutlet UIPickerView *pickerView;
@property (weak, nonatomic) IBOutlet UILabel *label;

@property (nonatomic, strong) NSDictionary *pickerData;
@property (nonatomic, strong) NSArray *pickerProvincesData;
@property (nonatomic, strong) NSArray *pickerCitiesData;
- (IBAction)onClick:(UIButton *)sender;

@end

