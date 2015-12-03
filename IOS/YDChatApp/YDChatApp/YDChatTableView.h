//
//  YDChatTableView.h
//  YDChatApp
//
//  Created by sijiewang on 12/1/15.
//  Copyright © 2015 lnmcc. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "YDChatTableViewDataSource.h"

typedef enum _CharBubbleTypeingType {
    ChatBubbleTypingTypeNobody = 0,
    ChatBubbleTypingTypeMe = 1,
    ChatBubbleTypingTypeSomeone = 2
} ChatBubbleTypingType;

@interface YDChatTableView : UITableView

@property (nonatomic, assign) id<YDChatTableViewDataSource> chatDataSource;
@property (nonatomic) NSTimeInterval snapInterval;
@property (nonatomic) ChatBubbleTypingType typeingBubble;

@end
