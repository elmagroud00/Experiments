//
//  ViewController.m
//  AddressBook
//
//  Created by sijiewang on 6/29/15.
//  Copyright (c) 2015 lnmcc. All rights reserved.
//

#import "ViewController.h"
#import "CustomCell.h"

@interface ViewController ()

@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view, typically from a nib.
    CFErrorRef error = NULL;
    ABAddressBookRef addressBook = ABAddressBookCreateWithOptions(NULL, &error);
    ABAddressBookRequestAccessWithCompletion(addressBook, ^(bool granted, CFErrorRef error) {
        if (granted) {
            // Search All
            [self filterContentForSearchText:@""];
        }
    });
    CFRelease(addressBook);
}

- (void)filterContentForSearchText:(NSString *)searchText {
    if (ABAddressBookGetAuthorizationStatus() != kABAuthorizationStatusAuthorized) {
        return;
    }
    CFErrorRef error = NULL;
    ABAddressBookRef addressBook = ABAddressBookCreateWithOptions(NULL, &error);
    if ([searchText length] == 0) {
        //search all
        self.listContracts = CFBridgingRelease(ABAddressBookCopyArrayOfAllPeople(addressBook));
    } else {
        CFStringRef cfSearchText = (CFStringRef)CFBridgingRetain(searchText);
        self.listContracts = CFBridgingRelease(ABAddressBookCopyPeopleWithName(addressBook, cfSearchText));
        CFRelease(cfSearchText);
    }
    [self.tableView reloadData];
    CFRelease(addressBook);
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (void)searchBarCancelButtonClicked:(UISearchBar *)searchBar {
    [self filterContentForSearchText:@""];
}

- (BOOL) searchDisplayController:(UISearchDisplayController *)controller shouldReloadTableForSearchString:(NSString *)searchString {
    [self filterContentForSearchText:searchString];
    return YES;
}

- (UITableViewCell*)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {
    static NSString *CellIdentifier = @"Cell";
    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:CellIdentifier];
    if (cell == nil) {
        cell = [[UITableViewCell alloc]initWithStyle:UITableViewCellStyleDefault reuseIdentifier:CellIdentifier];
    }
    ABRecordRef thisPerson = CFBridgingRetain([self.listContracts objectAtIndex:[indexPath row]]);
    NSString *firstName = CFBridgingRelease(ABRecordCopyValue(thisPerson, kABPersonFirstNameProperty));
    NSLog(@"firstName: %@", firstName);
    cell.textLabel.text = firstName;//[NSString stringWithFormat:@"%@", firstName];
    CFRelease(thisPerson);
    return cell;
}

-(NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section {
    NSLog(@"Count: %lu", [self.listContracts count]);
    return [self.listContracts count];
}

@end
