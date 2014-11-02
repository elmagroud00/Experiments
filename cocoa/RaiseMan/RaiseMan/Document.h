//
//  Document.h
//  RaiseMan
//
//  Created by sijiewang on 10/27/14.
//  Copyright (c) 2014 lnmcc. All rights reserved.
//

#import <Cocoa/Cocoa.h>

@class Person;

@interface Document : NSDocument
{
    NSMutableArray *employees;
    IBOutlet NSTableView *tableView;
    IBOutlet NSArrayController *employeeController;
}
-(void)setEmployee:(NSMutableArray*)a;
-(void)insertObject:(Person*)p inEmployeesAtIndex:(NSUInteger)index;
-(void)removeObjectFromEmployeesAtIndex:(NSUInteger)index;
-(IBAction)createEmployee:(id)sender;
@end

