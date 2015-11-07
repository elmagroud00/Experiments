//
//  BNRItem.h
//  Homepwner
//
//  Created by sijiewang on 11/7/15.
//  Copyright © 2015 lnmcc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreData/CoreData.h>
#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

@interface BNRItem : NSManagedObject

- (void)setThumbnailFromImage:(UIImage*)image;

@end

NS_ASSUME_NONNULL_END

#import "BNRItem+CoreDataProperties.h"
