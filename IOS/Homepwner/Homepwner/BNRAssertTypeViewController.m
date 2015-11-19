//
//  BNRAssertTypeViewController.m
//  Homepwner
//
//  Created by sijiewang on 11/16/15.
//  Copyright © 2015 lnmcc. All rights reserved.
//

#import "BNRAssertTypeViewController.h"
#import "BNRItemStore.h"
#import "BNRItem.h"
#import <CoreData/CoreData.h>

@implementation BNRAssertTypeViewController

- (instancetype)init {
    return [super initWithStyle:UITableViewStylePlain];
}

- (instancetype) initWithStyle:(UITableViewStyle)style {
    return [self init];
}

- (void)viewDidLoad {
    [super viewDidLoad];
    [self.tableView registerClass: [UITableViewCell class] forCellReuseIdentifier:@"UITableViewCell"];
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section {
    return [[[BNRItemStore sharedStore] allAssertTypes] count];
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {
    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:@"UITableViewCell"];
    NSArray *allAsserts = [[BNRItemStore sharedStore] allAssertTypes];
    NSManagedObject *assertType = allAsserts[indexPath.row];
    
    NSString *assertLabel = [assertType valueForKey:@"label"];
    [cell.textLabel setText:assertLabel];
    
    if (assertType == self.item.assertType) {
        cell.accessoryType = UITableViewCellAccessoryCheckmark;
    } else {
        cell.accessoryType = UITableViewCellAccessoryNone;
    }
    
    return cell;
}

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath {
    UITableViewCell *cell = [tableView cellForRowAtIndexPath:indexPath];
    cell.accessoryType = UITableViewCellAccessoryCheckmark;
    NSArray *allAssert = [[BNRItemStore sharedStore] allAssertTypes];
    NSManagedObject *assertType = allAssert[indexPath.row];
    self.item.assertType = assertType;
    [self.navigationController popViewControllerAnimated:YES];
}

@end
