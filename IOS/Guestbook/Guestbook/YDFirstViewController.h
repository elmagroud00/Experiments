//
//  YDFirstViewController.h
//  Guestbook
//
//  Created by sijiewang on 12/21/15.
//  Copyright © 2015 lnmcc. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface YDFirstViewController : UIViewController
@property(nonatomic, strong) NSMutableDictionary *postion;
@property(nonatomic, weak) IBOutlet UITableView *mTableView;
@end
