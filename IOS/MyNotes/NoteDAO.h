//
//  NoteDAO.h
//  MyNotes
//
//  Created by sijiewang on 6/13/15.
//  Copyright (c) 2015 lnmcc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "Note.h"

@interface NoteDAO : NSObject

@property (nonatomic, strong) NSMutableArray *listData;

+ (NoteDAO*)sharedManager;

- (int)create:(Note*)model;
- (int)remove:(Note*)model;
- (int)modify:(Note*)model;
- (NSMutableArray*)findAll;
- (Note*) findById:(Note*)model;

- (NSString*)applicationDocumentsDirectoryFile;
- (void)createEditableCopyOfDatabaseIfNeeded;

@end
