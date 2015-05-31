//
//  ViewController.h
//  SimpleTable
//
//  Created by sijiewang on 5/29/15.
//  Copyright (c) 2015 lnmcc. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface ViewController : UITableViewController <UITableViewDataSource, UITableViewDelegate>
@property (nonatomic, strong) NSArray *listTeams;

@end

