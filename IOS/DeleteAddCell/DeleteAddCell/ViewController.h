//
//  ViewController.h
//  DeleteAddCell
//
//  Created by sijiewang on 6/2/15.
//  Copyright (c) 2015 lnmcc. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface ViewController : UIViewController <UITableViewDataSource,
UITableViewDelegate, UITextFieldDelegate>

@property (nonatomic, strong) NSMutableArray *listTeams;

@property (weak, nonatomic) IBOutlet UINavigationItem *navigationItem2;
@property (weak, nonatomic) IBOutlet UITableView *tableView;
@property (strong, nonatomic) IBOutlet UITextField *txtField;

@end

