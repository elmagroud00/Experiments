//
//  ViewController.m
//  ModalViewSample
//
//  Created by sijiewang on 6/3/15.
//  Copyright (c) 2015 lnmcc. All rights reserved.
//

#import "ViewController.h"

@interface ViewController ()

@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view, typically from a nib.
    [[NSNotificationCenter defaultCenter] addObserver:self  selector:@selector(registerCompletion:) name:@"RegisterCompletionNotification" object:nil];
}

- (void)registerCompletion:(NSNotification*)notification {
    NSDictionary *theData = [notification userInfo];
    NSString *username = [theData objectForKey:@"username"];
    NSLog(@"username = %@", username);
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (IBAction)regonclick:(id)sender {
    UIStoryboard *mainStoryboard = [UIStoryboard storyboardWithName:@"Main" bundle:nil];
    UIViewController *registerViewController = [mainStoryboard instantiateViewControllerWithIdentifier:@"registerViewController"];
    registerViewController.modalTransitionStyle = UIModalTransitionStyleCoverVertical;
    [self presentViewController:registerViewController animated:YES completion:^ {
        NSLog(@"Present Modal View");
    }];
}
@end
