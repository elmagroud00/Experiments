//
//  ViewController.m
//  TestKVC
//
//  Created by sijiewang on 5/15/16.
//  Copyright © 2016 lnmcc. All rights reserved.
//

#import "ViewController.h"
#import "Account.h"
#import "Person.h"

@interface ViewController ()

@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view, typically from a nib.
    
    Person *person1 = [[Person alloc] init];
    [person1 setValue:@"Kenshin" forKey:@"name"];
    [person1 setValue:@28 forKey:@"age"];
    [person1 showMessage];
    NSLog(@"Person1's name is : %@, age is %@", person1.name, [person1 valueForKey:@"age"]);
    
    Account *account1 = [[Account alloc] init];
    person1.account = account1;
    [person1 setValue:@10000000.0 forKeyPath:@"account.balance"];
    NSLog(@"Person1's balance is : %.2f", [[person1 valueForKeyPath:@"account.balance"] floatValue]);
    
    account1.balance = 200000000.0;
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

@end
