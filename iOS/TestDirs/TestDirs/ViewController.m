//
//  ViewController.m
//  TestDirs
//
//  Created by sijiewang on 4/14/16.
//  Copyright © 2016 lnmcc. All rights reserved.
//

#import "ViewController.h"

@interface ViewController ()

@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view, typically from a nib.
    NSFileManager *fileManager = [NSFileManager defaultManager];
    NSString *entry;
    NSDirectoryEnumerator *enumerator;
    BOOL isDir;
    NSString *dir;
    
    //dir = NSHomeDirectory();
    dir = @"./";
    NSLog(@"Home Dir: %@", dir);
    
    //NSString *homeDir = [@"~"];
    

    
    [fileManager changeCurrentDirectoryPath:@"~"];
    enumerator = [fileManager enumeratorAtPath:dir];
    while ((entry = [enumerator nextObject]) != nil) {
        //NSLog(@"File - %@", entry);
        //if ([entry containsString:@"a.jpg"]) {
            NSLog(@"File - %@", entry);
        //}
    }
     NSLog(@"End");
    
    //NSURL *url = [NSURL fileURLWithPath:@"file:///"];

}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

@end
