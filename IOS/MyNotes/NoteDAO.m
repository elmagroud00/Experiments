//
//  NoteDAO.m
//  MyNotes
//
//  Created by sijiewang on 6/13/15.
//  Copyright (c) 2015 lnmcc. All rights reserved.
//

#import "NoteDAO.h"

@implementation NoteDAO

static NoteDAO* sharedManager = nil;

+ (NoteDAO*)sharedManager {
    //static dispatch_once_t once;
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        sharedManager = [[self alloc]init];
        [sharedManager createEditableCopyOfDatabaseIfNeeded];
    });
    /*
    dispatch_once(&once, ^{
        NSDateFormatter *dateFormatter = [[NSDateFormatter alloc]init];
        [dateFormatter setDateFormat:@"yyyy-MM-dd HH:mm:ss"];
        NSDate *date1 = [dateFormatter dateFromString:@"2010-08-04 16:01:03"];
        Note* note1 = [[Note alloc]init];
        note1.date = date1;
        note1.content = @"Welcome to MyNotes";
        
        NSDate *date2 = [dateFormatter dateFromString:@"2011-12-04 16:01:03"];
        Note* note2 = [[Note alloc]init];
        note2.date = date2;
        note2.content = @"欢迎使用MyNote。";
        
        sharedManager = [[self alloc]init];
        sharedManager.listData = [[NSMutableArray alloc]init];
        [sharedManager.listData addObject:note1];
        [sharedManager.listData addObject:note2];
    });
     */
    return sharedManager;
}

- (int) create:(Note *)model {
    //[self.listData addObject:model];
    NSString *path = [self applicationDocumentsDirectoryFile];
    NSFileManager *fileManager = [NSFileManager defaultManager];
    if (![fileManager fileExistsAtPath:path]) {
        [self createEditableCopyOfDatabaseIfNeeded];
    }
    
    NSMutableArray *array = [[NSMutableArray alloc]initWithContentsOfFile:path];
    NSDateFormatter *dateFormatter = [[NSDateFormatter alloc]init];
    [dateFormatter setDateFormat:@"yyyy-MM-dd HH:mm:ss"];
    NSDictionary *dict = [NSDictionary dictionaryWithObject:@[[dateFormatter stringFromDate:model.date]] forKey:model.content];
    [array addObject:dict];
    [array writeToFile:path atomically:YES];
    
    return 0;
}

- (int) remove:(Note *)model {
    NSString *path = [self applicationDocumentsDirectoryFile];
    NSMutableArray *array = [[NSMutableArray alloc]initWithContentsOfFile:path];
    
    for (NSDictionary *dict in array) {
        NSDateFormatter *dateFormatter = [[NSDateFormatter alloc]init];
        [dateFormatter setDateFormat:@"yyyy-MM-dd HH:mm:ss"];
        
        NSDate *date = [dateFormatter dateFromString:[dict objectForKey:@"date"]];
        
        if ([date isEqualToDate:model.date]) {
            [array removeObject: dict];
            [array writeToFile:path atomically:YES];
            break;
        }
    }
    /*
    for (Note *note in self.listData) {
        if ([note.date isEqualToDate:model.date]) {
            [self.listData removeObject:note];
            break;
        }
    }*/
    return 0;
}

- (int) modify:(Note *)model {
    NSString *path = [self applicationDocumentsDirectoryFile];
    NSMutableArray *array = [[NSMutableArray alloc]initWithContentsOfFile:path];
    
    for (NSDictionary *dict in array) {
        NSDateFormatter *dateFormatter = [[NSDateFormatter alloc]init];
        [dateFormatter setDateFormat:@"yyyy-MM-dd HH:mm:ss"];
        NSDate *date = [dateFormatter dateFromString:[dict objectForKey:@"date"]];
        NSString *content = [dict objectForKey:@"content"];
        
        if ([date isEqualToDate:model.date]) {
            [dict setValue:content forKey:@"content"];
            [array writeToFile:path atomically:YES];
            break;
        }
    }
    /*
    for (Note* note in self.listData) {
        if ([note.date isEqualToDate:model.date]) {
            note.content = model.content;
            break;
        }
    }*/
    return 0;
}

- (NSMutableArray*) findAll {
    return self.listData;
}

- (Note*) findById:(Note *)model {
    for (Note* note in self.listData) {
        if ([note.date isEqualToDate:model.date]) {
            return note;
        }
    }
    return nil;
}

- (void)createEditableCopyOfDatabaseIfNeeded {
    NSFileManager *fileManager = [NSFileManager defaultManager];
    NSString *writeableDBPath = [self applicationDocumentsDirectoryFile];
    
    NSLog(@"writeableDBPath: %@", writeableDBPath);
    
    BOOL dbexists = [fileManager fileExistsAtPath:writeableDBPath];
    if (!dbexists) {
        NSString *defaultDBPath = [[NSBundle mainBundle]pathForResource:@"NotesList" ofType:@"plist"];
        NSLog(@"defaultDBPath: %@", defaultDBPath);
        if ([fileManager fileExistsAtPath:defaultDBPath]) {
            NSLog(@"Default DB file Exist");
        }
        NSError *error;
        NSString *dstDirector = [NSSearchPathForDirectoriesInDomains(NSDocumentationDirectory, NSUserDomainMask, YES) lastObject];
        BOOL success = [fileManager copyItemAtPath:defaultDBPath toPath:dstDirector error:&error];
        if (!success) {
            NSAssert1(0, @"错误写入文件： %@", [error localizedDescription]);
        }
    }
}

- (NSString*)applicationDocumentsDirectoryFile {
    NSString *documentDirectory = [NSSearchPathForDirectoriesInDomains(NSDocumentationDirectory, NSUserDomainMask, YES) lastObject];
    NSString *path = [documentDirectory stringByAppendingPathComponent:@"NotesList.plist"];
    NSLog(@"path: %@", path);
    return path;
}

@end
