//
//  NoteBL.m
//  MyNotes
//
//  Created by sijiewang on 6/13/15.
//  Copyright (c) 2015 lnmcc. All rights reserved.
//

#import "NoteBL.h"
#import "NoteDAO.h"

@implementation NoteBL
- (NSMutableArray*)createNote:(Note *)model {
    NoteDAO *dao = [NoteDAO sharedManager];
    [dao create:model];
    
    return  [dao findAll];
}

- (NSMutableArray*)remove:(Note *)model {
    NoteDAO *dao = [NoteDAO sharedManager];
    [dao remove:model];
    
    return [dao findAll];
}

- (NSMutableArray*)findAll {
    NoteDAO *dao = [NoteDAO sharedManager];
    return [dao findAll];
}

@end
