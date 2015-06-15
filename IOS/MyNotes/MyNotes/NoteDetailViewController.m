//
//  NoteDetailViewController.m
//  MyNotes
//
//  Created by sijiewang on 6/13/15.
//  Copyright (c) 2015 lnmcc. All rights reserved.
//

#import "NoteDetailViewController.h"

@interface NoteDetailViewController ()

@end

@implementation NoteDetailViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view.
    self.noteDetail.text = self.data;
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (void)setText:(NSString *)text {
    NSLog(@"%@", text);
    self.noteDetail.text = @"set Text";
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
