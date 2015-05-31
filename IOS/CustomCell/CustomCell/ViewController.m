//
//  ViewController.m
//  CustomCell
//
//  Created by sijiewang on 5/31/15.
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
    NSBundle *bundle = [NSBundle mainBundle];
    NSString *plistPath = [bundle pathForResource:@"team" ofType:@"plist"];
    if (plistPath == nil) {
        NSLog(@"%s", "plistPath is nil");
    }
    
    self.listTeams = [[NSArray alloc] initWithContentsOfFile:plistPath];
    for(NSDictionary *dic in self.listTeams) {
        NSString *name = [dic objectForKey:@"name"];
        NSLog(@"%@", name);
    }
    
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section {
    return [self.listTeams count];
}

- (UITableViewCell*)tableView:(UITableView*)tableView
        cellForRowAtIndexPath:(NSIndexPath *)indexPath {
    static NSString *CellIdentifier = @"Cell";
    CustomCell *cell = [tableView dequeueReusableCellWithIdentifier:CellIdentifier];
    
    if(cell == nil) {
        cell = [[CustomCell alloc] initWithStyle:UITableViewCellStyleDefault reuseIdentifier:CellIdentifier];
    }
    
    NSUInteger row = [indexPath row];
    NSDictionary *rowDict = [self.listTeams objectAtIndex:row];
    cell.name.text = [rowDict objectForKey:@"name"];
    NSLog(@"Label name %@", [rowDict objectForKey:@"name"]);
    
    NSString *imagePath = [rowDict objectForKey:@"image"];
    
    imagePath = [imagePath stringByAppendingString:@"gif"];
    
    cell.image.image = [UIImage imageNamed: imagePath];
    cell.accessoryType = UITableViewCellAccessoryDisclosureIndicator;
    return cell;
}

@end
