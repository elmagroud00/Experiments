//
//  ViewController.m
//  TestFilePath
//
//  Created by sijiewang on 4/27/16.
//  Copyright © 2016 lnmcc. All rights reserved.
//

#import "ViewController.h"

@interface ViewController ()

@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view, typically from a nib.
    
    NSString *path = [[NSBundle mainBundle] resourcePath];
    NSLog(@"Path = %@", path);
    
    NSString *filePath = [path stringByAppendingPathComponent:@"01.jpg"];
    NSLog(@"File Path = %@", filePath);
    NSData *data = [NSData dataWithContentsOfFile:filePath];
    NSLog(@"Data = %@", data);
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

@end
