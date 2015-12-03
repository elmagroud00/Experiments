//
//  YDChatTableViewHeaderCell.h
//  YDChatApp
//
//  Created by sijiewang on 12/2/15.
//  Copyright © 2015 lnmcc. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <Foundation/Foundation.h>

@interface YDChatTableViewHeaderCell : UITableViewCell

@property (nonatomic, strong) NSDate *date;

+ (CGFloat)height;

@end
