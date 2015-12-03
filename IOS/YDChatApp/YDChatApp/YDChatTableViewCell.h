//
//  YDChatTableViewCell.h
//  YDChatApp
//
//  Created by sijiewang on 12/2/15.
//  Copyright © 2015 lnmcc. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "YDChatData.h"

@interface YDChatTableViewCell : UITableViewCell

@property (nonatomic, strong) YDChatData *data;

- (void)setData:(YDChatData *)data;

@end
