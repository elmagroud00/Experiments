//
//  NoteDetailViewController.h
//  MyNotes
//
//  Created by sijiewang on 6/13/15.
//  Copyright (c) 2015 lnmcc. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface NoteDetailViewController : UIViewController

@property (weak, nonatomic) IBOutlet UITextView *noteDetail;
@property (nonatomic, copy) NSString *data;

- (void)setText:(NSString*)text;

@end
