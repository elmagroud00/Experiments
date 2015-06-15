//
//  ViewController.h
//  MyNotes
//
//  Created by sijiewang on 6/13/15.
//  Copyright (c) 2015 lnmcc. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "NoteBL.h"

@interface ViewController : UITableViewController <UITableViewDataSource, UITableViewDelegate> {
    
    @private NoteBL *noteBL;
    @private NSArray *notes;
    @private Note *currentNote;
}

@property (strong, nonatomic) IBOutlet UITableView *tableView;

@end

