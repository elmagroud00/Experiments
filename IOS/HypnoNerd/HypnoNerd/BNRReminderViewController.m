//
//  BNRReminderViewController.m
//  HypnoNerd
//
//  Created by sijiewang on 8/11/15.
//  Copyright (c) 2015 lnmcc. All rights reserved.
//

#import "BNRReminderViewController.h"

@interface BNRReminderViewController()

@property (nonatomic, weak) IBOutlet UIDatePicker *dataPicker;

@end

@implementation BNRReminderViewController

- (IBAction)addReminder:(id)sender {
    NSDate *date = self.dataPicker.date;
    NSLog(@"Setting a reminder for %@", date);
    
    UILocalNotification *note = [[UILocalNotification alloc]init];
    note.alertBody = @"Hypnote me !";
    note.fireDate = date;
    
    [[UIApplication sharedApplication] scheduleLocalNotification:note];
}

- (void)viewDidAppear:(BOOL)animated {
    [super viewDidAppear:animated];
    self.dataPicker.minimumDate = [NSDate dateWithTimeIntervalSinceNow:60];
}

@end
