//
//  YDViewController.h
//  JSONCars
//
//  Created by sijiewang on 12/11/15.
//  Copyright © 2015 lnmcc. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface YDViewController : UIViewController
@property (weak, nonatomic) IBOutlet UITableView *mTableView;
@property (nonatomic, strong) NSMutableArray *cars;
@end
