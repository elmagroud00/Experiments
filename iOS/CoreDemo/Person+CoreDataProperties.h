//
//  Person+CoreDataProperties.h
//  CoreDemo
//
//  Created by sijiewang on 1/21/16.
//  Copyright © 2016 lnmcc. All rights reserved.
//
//  Choose "Create NSManagedObject Subclass…" from the Core Data editor menu
//  to delete and recreate this implementation file for your updated model.
//

#import "Person.h"

NS_ASSUME_NONNULL_BEGIN

@interface Person (CoreDataProperties)

@property (nullable, nonatomic, retain) NSString *firstname;
@property (nullable, nonatomic, retain) NSString *lastname;
@property (nullable, nonatomic, retain) NSNumber *vip;

@end

NS_ASSUME_NONNULL_END
