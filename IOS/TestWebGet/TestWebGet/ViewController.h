//
//  ViewController.h
//  TestWebGet
//
//  Created by sijiewang on 7/4/15.
//  Copyright (c) 2015 lnmcc. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "String+URLEncoding.h"

@interface ViewController : UITableViewController <UITableViewDelegate, UITableViewDataSource, NSURLConnectionDataDelegate>

@property (nonatomic, strong) NSMutableArray *listData;
@property (strong, nonatomic) NSMutableData *datas;

-(void)reloadView:(NSDictionary*)res;
-(void)startRequest;
@end

