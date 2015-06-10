//
//  ViewController.m
//  TreeNavigation
//
//  Created by sijiewang on 6/6/15.
//  Copyright (c) 2015 lnmcc. All rights reserved.
//

#import "ViewController.h"
#import "CitiesViewController.h"

@interface ViewController ()

@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view, typically from a nib.
    self.tableView.delegate = self;
    self.tableView.dataSource = self;
    
    NSBundle *bundle = [NSBundle mainBundle];
    NSString *path = [bundle pathForResource:@"provinces_cities" ofType:@"plist"];
    
    self.dictData =[[NSDictionary alloc] initWithContentsOfFile:path];
    self.listData = [self.dictData allKeys];
    self.title = @"城市信息";
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section {
    return [self.listData count];
}

- (UITableViewCell*)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {
    static NSString *CellIdentifier = @"Cell";
    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:CellIdentifier forIndexPath:indexPath];
    NSInteger row = [indexPath row];
    cell.textLabel.text = [self.listData objectAtIndex:row];
    return cell;
}

- (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender {
    CitiesViewController *citiesViewController = segue.destinationViewController;
    NSInteger selectedIndex = [[self.tableView indexPathForSelectedRow] row];
    NSString *selectName = [self.listData objectAtIndex:selectedIndex];
    citiesViewController.listData = [self.dictData objectForKey:selectName];
    citiesViewController.title = selectName;
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

@end
