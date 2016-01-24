//
//  YDViewController.m
//  CoreDemo
//
//  Created by sijiewang on 1/21/16.
//  Copyright © 2016 lnmcc. All rights reserved.
//

#import "YDViewController.h"
#import <CoreData/CoreData.h>

@interface YDViewController ()

@end

@implementation YDViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view from its nib.
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (void)loadPeople {
    if (people)
        people = nil;
    people = [[NSMutableArray alloc] init];
    NSEntityDescription *entity = [NSEntityDescription entityForName:@"Person" inManagedObjectContext:[self ]]
    
    
}

/*
#pragma mark - Navigation

// In a storyboard-based application, you will often want to do a little preparation before navigation
- (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender {
    // Get the new view controller using [segue destinationViewController].
    // Pass the selected object to the new view controller.
}
*/

@end
