//
//  ViewController.h
//  SearchbarSimpleTable
//
//  Created by sijiewang on 5/31/15.
//  Copyright (c) 2015 lnmcc. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface ViewController : UITableViewController <UISearchBarDelegate, UISearchDisplayDelegate>

@property (weak, nonatomic) IBOutlet UISearchBar *searchBar;
@property (nonatomic, strong) NSArray *listTeams;
@property (nonatomic, strong) NSMutableArray *listFilterTeam;

- (void)filterContentForSearch:(NSString*)searchText scope:(NSUInteger)scope;

@end

