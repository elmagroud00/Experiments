//
//  ViewController.h
//  RSSReader
//
//  Created by sijiewang on 12/21/15.
//  Copyright © 2015 lnmcc. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface ViewController : UIViewController

- (void)parseXMLFileAtURL: (NSString *)URL;

@property(nonatomic, weak) IBOutlet UITableView *mTableView;
@property(nonatomic, strong) NSMutableArray *feeds;

@end

