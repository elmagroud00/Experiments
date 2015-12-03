//
//  YDChatTableViewHeaderCell.m
//  YDChatApp
//
//  Created by sijiewang on 12/2/15.
//  Copyright © 2015 lnmcc. All rights reserved.
//

#import "YDChatTableViewHeaderCell.h"
#import <Foundation/Foundation.h>

@interface YDChatTableViewHeaderCell()

@property (nonatomic, retain) UILabel *label;

@end

@implementation YDChatTableViewHeaderCell

+ (CGFloat)height {
    return 30.0;
}

- (void)setDate: (NSDate *)value {
    NSDateFormatter *dateFormatter = [[NSDateFormatter alloc] init];
    [dateFormatter setDateStyle:NSDateFormatterMediumStyle];
    [dateFormatter setTimeStyle:NSDateFormatterShortStyle];
    NSString *text = [dateFormatter stringFromDate:value];
    if (self.label) {
        self.label.text = text;
        return;
    }
    self.selectionStyle = UITableViewCellSelectionStyleNone;
    self.label = [[UILabel alloc] initWithFrame:CGRectMake(0, 0, self.frame.size.width, self.frame.size.height)];
    self.label.text = text;
    self.label.font = [UIFont boldSystemFontOfSize:12];
    self.label.textAlignment = NSTextAlignmentCenter;
    self.label.shadowOffset = CGSizeMake(0, 1);
    self.label.textColor = [UIColor darkGrayColor];
    self.label.backgroundColor = [UIColor clearColor];
    [self addSubview:self.label];
}

@end
