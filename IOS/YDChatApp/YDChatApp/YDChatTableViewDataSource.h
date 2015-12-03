//
//  YDChatTableViewDataSource.h
//  YDChatApp
//
//  Created by sijiewang on 12/1/15.
//  Copyright © 2015 lnmcc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "YDChatData.h"
#import "YDChatTableView.h"

@class YDChatData;
@class YDChatTableView;

@protocol YDChatTableViewDataSource <NSObject>

- (NSInteger)rowsForChatTable: (YDChatTableView *)tableView;
- (YDChatData *)chatTableView: (YDChatTableView *)tableView  dataForRow: (NSInteger)row;

@end