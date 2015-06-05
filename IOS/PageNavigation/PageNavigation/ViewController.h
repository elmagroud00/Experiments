//
//  ViewController.h
//  PageNavigation
//
//  Created by sijiewang on 6/5/15.
//  Copyright (c) 2015 lnmcc. All rights reserved.
//

#import <UIKit/UIKit.h>

typedef NS_ENUM(NSInteger, DirectionForward) {
    Before,
    After,
};

@interface ViewController : UIViewController <UIPageViewControllerDataSource, UIPageViewControllerDelegate> {

    int pageIndex;
    DirectionForward direction;
}

@property (strong, nonatomic) UIPageViewController *pageViewController;

@end

