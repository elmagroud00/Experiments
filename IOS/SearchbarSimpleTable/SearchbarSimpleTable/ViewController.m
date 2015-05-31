//
//  ViewController.m
//  SearchbarSimpleTable
//
//  Created by sijiewang on 5/31/15.
//  Copyright (c) 2015 lnmcc. All rights reserved.
//

#import "ViewController.h"

@interface ViewController ()

@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view, typically from a nib.
    
    [self.searchBar setShowsScopeBar:NO];
    [self.searchBar sizeToFit];
    
    NSBundle *bundle = [NSBundle mainBundle];
    NSString *plistPath = [bundle pathForResource:@"team" ofType:@"plist"];
    
    self.listTeams = [[NSArray alloc] initWithContentsOfFile:plistPath];
    
    [self filterContentForSearch:@"" scope:-1];
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (BOOL)searchDisplayController:(UISearchDisplayController *)controller shouldReloadTableForSearchString:(NSString *)searchString {
    [self filterContentForSearch:searchString scope:self.searchBar.selectedScopeButtonIndex];
    return YES;
}

-(BOOL) searchDisplayController:(UISearchDisplayController *)controller shouldReloadTableForSearchScope:(NSInteger)searchOption {
    [self filterContentForSearch:self.searchBar.text scope:searchOption];
    return YES;
}

- (void)searchBarCancelButtonClicked:(UISearchBar *)searchBar {
    [self filterContentForSearch:@"" scope:-1];
}

- (NSInteger) tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section {
    return [self.listFilterTeam count];
}

-(UITableViewCell*)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {
    
    static NSString *cellIdentifer = @"CellIdentifier";
    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:cellIdentifer];
    if(cell == nil) {
        cell = [[UITableViewCell alloc] initWithStyle:UITableViewCellStyleDefault reuseIdentifier:cellIdentifer];
    }
    NSUInteger row = [indexPath row];
    NSDictionary *rowDict = [self.listFilterTeam objectAtIndex:row];
    cell.textLabel.text = [rowDict objectForKey:@"name"];
    
    NSString *imagePath = [rowDict objectForKey:@"image"];
    imagePath = [imagePath stringByAppendingString:@"gif"];
    
    cell.imageView.image = [UIImage imageNamed:imagePath];
    
    cell.accessoryType = UITableViewCellAccessoryDisclosureIndicator;
    
    return cell;
}

- (void)filterContentForSearch:(NSString *)searchText scope:(NSUInteger)scope {
    if ([searchText length] == 0) {
        self.listFilterTeam = [NSMutableArray arrayWithArray:self.listTeams];
        return;
    }
    NSPredicate *scopePredicate;
    NSArray *tempArray;
    
    switch (scope) {
        case 0:
            scopePredicate = [NSPredicate predicateWithFormat:@"SELF.name contains[c] %@", searchText];
            tempArray = [self.listTeams filteredArrayUsingPredicate:scopePredicate];
            self.listFilterTeam = [NSMutableArray arrayWithArray:tempArray];
            break;
        case 1:
            scopePredicate = [NSPredicate predicateWithFormat:@"SELF.image contains[c] %@", searchText];
            tempArray = [self.listTeams filteredArrayUsingPredicate:scopePredicate];
            self.listFilterTeam = [NSMutableArray arrayWithArray:tempArray];
            break;
            
        default:
            self.listFilterTeam = [NSMutableArray arrayWithArray:self.listTeams];
            break;
    }
}

@end
