//
//  NoteManagerObject.h
//  TestCoreData2
//
//  Created by sijiewang on 6/28/15.
//  Copyright (c) 2015 lnmcc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreData/CoreData.h>


@interface NoteManagerObject : NSManagedObject

@property (nonatomic, retain) NSDate * date;
@property (nonatomic, retain) NSString * content;

@end
