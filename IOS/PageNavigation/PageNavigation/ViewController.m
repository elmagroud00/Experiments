//
//  ViewController.m
//  PageNavigation
//
//  Created by sijiewang on 6/5/15.
//  Copyright (c) 2015 lnmcc. All rights reserved.
//

#import "ViewController.h"

@interface ViewController ()

@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view, typically from a nib.
    self.pageViewController = [[UIPageViewController alloc]initWithTransitionStyle:(UIPageViewControllerTransitionStylePageCurl) navigationOrientation:UIPageViewControllerNavigationOrientationHorizontal options:nil];
    
    self.pageViewController.delegate = self;
    self.pageViewController.dataSource = self;
    
    UIStoryboard *mainStoryboard = [UIStoryboard storyboardWithName:@"Main" bundle:nil];
    UIViewController *page1ViewController = [mainStoryboard instantiateViewControllerWithIdentifier:@"page1"];
    
    NSArray *viewControllers = @[page1ViewController];
    [self.pageViewController setViewControllers:viewControllers direction:UIPageViewControllerNavigationDirectionForward animated:YES completion:nil];
    
    [self.view addSubview:self.pageViewController.view];
    pageIndex = 0;
}

- (UIViewController*)pageViewController:(UIPageViewController *)pageViewController viewControllerBeforeViewController:(UIViewController *)viewController {
    pageIndex--;
    if (pageIndex < 0) {
        pageIndex = 0;
        return nil;
    }
    
    direction = Before;
    UIStoryboard *mainStoryboard = [UIStoryboard storyboardWithName:@"Main" bundle:nil];
    NSString *pageId = [NSString stringWithFormat:@"page%i", pageIndex];
    UIViewController *pvController = [mainStoryboard instantiateViewControllerWithIdentifier:pageId];
    
    return pvController;
}

- (UIViewController*) pageViewController:(UIPageViewController *)pageViewController viewControllerAfterViewController:(UIViewController *)viewController {
    pageIndex++;
    
    if (pageIndex  > 2) {
        pageIndex = 2;
        return nil;
    }
    
    direction = After;
    UIStoryboard *mainStoryboard = [UIStoryboard storyboardWithName:@"Main" bundle:nil];
    NSString *pageId = [NSString stringWithFormat:@"page%i", pageIndex];
    UIViewController *pvController = [mainStoryboard instantiateViewControllerWithIdentifier:pageId];
    
    return pvController;
}

- (UIPageViewControllerSpineLocation)pageViewController:(UIPageViewController *)pageViewController spineLocationForInterfaceOrientation:(UIInterfaceOrientation)orientation {
    self.pageViewController.doubleSided = NO;
    return UIPageViewControllerSpineLocationMin;
}

- (void)pageViewController:(UIPageViewController *)pageViewController didFinishAnimating:(BOOL)finished previousViewControllers:(NSArray *)previousViewControllers transitionCompleted:(BOOL)completed {
    if (!completed) {
        if (direction == After) {
            pageIndex--;
        }
        if (direction == Before) {
            pageIndex++;
        }
    }
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

@end
