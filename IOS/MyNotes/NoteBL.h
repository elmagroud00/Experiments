//
//  NoteBL.h
//  MyNotes
//
//  Created by sijiewang on 6/13/15.
//  Copyright (c) 2015 lnmcc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "Note.h"

@interface NoteBL : NSObject

- (NSMutableArray*) createNote:(Note*)model;
- (NSMutableArray*) remove:(Note*)model;
- (NSMutableArray*) findAll;

@end
