//
//  BNRDetailViewController.h
//  Homepwner
//
//  Created by sijiewang on 8/20/15.
//  Copyright (c) 2015 lnmcc. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "BNRItem.h"
#import "BNRItemStore.h"
#import "BNRImageStore.h"

@class BNRItem;

@interface BNRDetailViewController : UIViewController 

@property (nonatomic, strong) BNRItem *item;
@property (nonatomic, copy) void (^dismissBlock)(void);

- (instancetype)initForNewItem:(BOOL)isNew;

@end
