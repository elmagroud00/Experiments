//
//  ViewController.h
//  AddressBook
//
//  Created by sijiewang on 6/29/15.
//  Copyright (c) 2015 lnmcc. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <AddressBook/AddressBook.h>

@interface ViewController : UITableViewController <UISearchBarDelegate, UISearchDisplayDelegate, UITableViewDataSource, UITableViewDelegate>

@property (nonatomic, strong) NSArray *listContracts;

-(void) filterContentForSearchText:(NSString*)searchText;
@property (strong, nonatomic) IBOutlet UITableView *tableView;

@end

