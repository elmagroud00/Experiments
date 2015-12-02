//
//  YDChatTableViewDataSource.h
//  YDChatApp
//
//  Created by sijiewang on 12/1/15.
//  Copyright © 2015 lnmcc. All rights reserved.
//

#import <Foundation/Foundation.h>

@class YDChatData;
@class TDChatTableView;

@protocol YDChatTableViewDataSource <NSObject>

- (NSInteger) rowsForChatTable: (YDChatTableView *)tableView;
- (YDChatData *) chatTableView: (YDChatTableView *)tableView  dataForRow: (NSInteger)row;

@end