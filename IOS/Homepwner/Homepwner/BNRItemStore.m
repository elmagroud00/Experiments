//
//  BNRItemStore.m
//  Homepwner
//
//  Created by sijiewang on 8/15/15.
//  Copyright (c) 2015 lnmcc. All rights reserved.
//

#import "BNRItemStore.h"
#import "BNRItem.h"

@interface BNRItemStore()

@property (nonatomic) NSMutableArray *privateItems;

@end

@implementation BNRItemStore

+ (instancetype)sharedStore {
    static BNRItemStore *sharedStore = nil;
    
    if (!sharedStore) {
        sharedStore = [[self alloc]initPrivate];
    }
    return  sharedStore;
}

- (instancetype)init {
    @throw [NSException exceptionWithName:@"Singleton" reason:@"User + [BNRItemStore sharedStore]" userInfo:nil];
    return nil;
}

- (instancetype)initPrivate {
    self = [super init];
    if (self) {
        _privateItems = [[NSMutableArray alloc]init];
    }
    
    return self;
}

- (NSArray *)allItems {
    return self.privateItems;
}

- (BNRItem *)createItem {
    BNRItem *item = [BNRItem randomItem];
    [self.privateItems addObject:item];
    return item;
}

@end
