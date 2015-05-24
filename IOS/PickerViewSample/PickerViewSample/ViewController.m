//
//  ViewController.m
//  PickerViewSample
//
//  Created by sijiewang on 5/23/15.
//  Copyright (c) 2015 lnmcc. All rights reserved.
//

#import "ViewController.h"

@interface ViewController ()

@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view, typically from a nib.
    NSBundle *bundle = [NSBundle mainBundle];
    NSString *plistPath = [bundle pathForResource:@"provinces_cities" ofType:@"plist"];
    NSDictionary *dict = [[NSDictionary alloc] initWithContentsOfFile:plistPath];
    self.pickerData = dict;
    self.pickerProvincesData = [self.pickerData allKeys];
    
    NSString *selectedProvincesData = [self.pickerProvincesData objectAtIndex:0];
    self.pickerCitiesData = [self.pickerData objectForKey:selectedProvincesData];
    
    self.pickerView.dataSource = self;
    self.pickerView.delegate = self;
}

- (NSString*) pickerView:(UIPickerView *)pickerView titleForRow:(NSInteger)row forComponent:(NSInteger)component {
    if (component == 0) {
        return [self.pickerProvincesData objectAtIndex:row];
    } else {
        return [self.pickerCitiesData objectAtIndex:row];
    }
}

- (void) pickerView:(UIPickerView *)pickerView didSelectRow:(NSInteger)row inComponent:(NSInteger)component {
    if (component == 0) {
        NSString *selectedProvince = [self.pickerProvincesData objectAtIndex:row];
        NSArray *array = [self.pickerData objectForKey:selectedProvince];
        self.pickerCitiesData = array;
        [self.pickerView reloadComponent:1];
    }
}


- (NSInteger) numberOfComponentsInPickerView:(UIPickerView *)pickerView {
    return 2;
}

- (NSInteger) pickerView:(UIPickerView *)pickerView numberOfRowsInComponent:(NSInteger)component {
    
    if (component == 0) {
        return [self.pickerProvincesData count];
    } else {
        return [self.pickerCitiesData count];
    }
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (IBAction)onClick:(UIButton *)sender {
    NSInteger row1 = [self.pickerView selectedRowInComponent:0];
    NSInteger row2 = [self.pickerView selectedRowInComponent:1];
    NSString *selected1 = [self.pickerProvincesData objectAtIndex:row1];
    NSString *selected2 = [self.pickerCitiesData objectAtIndex:row2];
    NSString *title = [[NSString alloc] initWithFormat:@"%@, %@市", selected1, selected2];
    self.label.text = title;
}
@end
