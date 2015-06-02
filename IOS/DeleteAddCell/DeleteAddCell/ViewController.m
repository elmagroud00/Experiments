//
//  ViewController.m
//  DeleteAddCell
//
//  Created by sijiewang on 6/2/15.
//  Copyright (c) 2015 lnmcc. All rights reserved.
//

#import "ViewController.h"

@interface ViewController ()

@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view, typically from a nib.
    self.navigationItem2.rightBarButtonItem = self.editButtonItem;
    self.navigationItem2.title = @"单元格插入和删除";
    
    self.txtField.hidden = YES;
    self.txtField.delegate = self;
    
    self.tableView.delegate = self;
    self.tableView.dataSource = self;
    
    self.listTeams = [[NSMutableArray alloc] initWithObjects:@"江苏", @"南通", @"海门", nil];
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (void)setEditing:(BOOL)editing animated:(BOOL)animated {
    [super setEditing:editing animated:animated];
    
    [self.tableView setEditing:editing animated:animated];
    if (editing) {
        self.txtField.hidden = NO;
    } else {
        self.txtField.hidden = YES;
    }
}

- (UITableViewCellEditingStyle)tableView:(UITableView*)tableView editingStyleForRowAtIndexPath:(NSIndexPath *)indexPath {
    if (indexPath.row == [self.listTeams count]) {
        return UITableViewCellEditingStyleInsert;
    } else {
        return UITableViewCellEditingStyleDelete;
    }
}

- (void)tableView:(UITableView *)tableView commitEditingStyle:(UITableViewCellEditingStyle)editingStyle forRowAtIndexPath:(NSIndexPath *)indexPath {
    if (editingStyle == UITableViewCellEditingStyleDelete) {
        [self.listTeams removeObjectAtIndex:indexPath.row];
        [self.tableView deleteRowsAtIndexPaths:[NSArray arrayWithObject:indexPath] withRowAnimation:UITableViewRowAnimationFade];
        [self.tableView reloadData];
    } else if (editingStyle == UITableViewCellEditingStyleInsert) {
        [self.listTeams insertObject:self.txtField.text atIndex:[self.listTeams count]];
        [self.tableView insertRowsAtIndexPaths:[NSArray arrayWithObject:indexPath] withRowAnimation:UITableViewRowAnimationFade];
        [self.tableView reloadData];
    }
}

- (BOOL)textFieldShouldReturn:(UITextField *)textField {
    [textField resignFirstResponder];
    return YES;
}

- (BOOL)tableView:(UITableView*)tableView shouldHighlightRowAtIndexPath:(NSIndexPath *)indexPath {
    if (indexPath.row == [self.listTeams count]) {
        return NO;
    } else {
        return YES;
    }
}

- (void)keyboardDidHide: (NSNotification*)notif {
    //[self.tableView setContentOffset:CGPointMake(0.0, 100.0) animated:YES];
}

- (void)viewWillDisappear:(BOOL)animated {
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(keyboardDidHide:) name:UIKeyboardDidHideNotification object:nil];
    [super viewDidAppear:animated];
}

- (void)textFieldDidBeginEditing:(UITextField *)textField {
    UITableViewCell *cell = (UITableViewCell*)[[textField superview] superview];
    [self.tableView setContentOffset:CGPointMake(0.0, cell.frame.origin.y) animated:YES];
}

- (CGFloat)tableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath {
    return 50;
}

- (UITableViewCell*) tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {
    static NSString *CellIdentifier = @"Cell";
    BOOL b_addCell = (indexPath.row == self.listTeams.count);
    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:CellIdentifier];
    if (cell == nil) {
        cell = [[UITableViewCell alloc]initWithStyle:UITableViewCellStyleDefault reuseIdentifier:CellIdentifier];
    }
    if (!b_addCell) {
        cell.accessoryType = UITableViewCellAccessoryDisclosureIndicator;
        cell.textLabel.text = [self.listTeams objectAtIndex:indexPath.row];
    } else {
        self.txtField.frame = CGRectMake(10, 0, 300, 44);
        self.txtField.text = @"";
        [cell.contentView addSubview:self.txtField];
    }
    return cell;
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section {
    return [self.listTeams count] + 1;
}

@end
