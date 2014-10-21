//
//  RandomController.m
//  Random
//
//  Created by sijiewang on 10/19/14.
//  Copyright (c) 2014 lnmcc. All rights reserved.
//

#import "RandomController.h"

@implementation RandomController

-(IBAction)generate:(id)sender {
    int generated;
    generated = (int)(random() % 100) + 1;
    NSLog(@"generated = %d", generated);
    
    [textField setIntValue: generated];
}

-(IBAction)seed:(id)sender:(id)sender {
    srandom((unsigned)time(NULL));
    [textField setStringValue:@"Generator seeded"];
}

-(void)awakeFromNib {
    NSDate *now;
    now = [NSDate date];
    [textField setObjectValue:now];
}
@end
