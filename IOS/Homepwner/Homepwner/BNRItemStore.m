//
//  BNRItemStore.m
//  Homepwner
//
//  Created by sijiewang on 8/15/15.
//  Copyright (c) 2015 lnmcc. All rights reserved.
//

#import "BNRItemStore.h"
#import "BNRItem.h"
#import "BNRImageStore.h"
#import <CoreData/CoreData.h>
@interface BNRItemStore()

@property (nonatomic) NSMutableArray *privateItems;
@property (nonatomic, strong) NSMutableArray *allAssertTypes;
@property (nonatomic, strong) NSManagedObjectContext *context;
@property (nonatomic, strong) NSManagedObjectModel *model;

@end

@implementation BNRItemStore

+ (instancetype)sharedStore {
    
    static BNRItemStore *sharedStore = nil;
    /*
    if (!sharedStore) {
        sharedStore = [[self alloc]initPrivate];
    }
     */
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        sharedStore = [[self alloc] initPrivate];
    });
    
    return  sharedStore;
}

- (NSString*)itemArchivePath {
    NSArray *documentDirectories =
    NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES);
    
    NSString *documentDirectory = [documentDirectories firstObject];
    NSLog(@"Document Directory: %@", documentDirectory);
    
    //return [documentDirectory stringByAppendingPathComponent:@"items.archive"];
    return [documentDirectory stringByAppendingPathComponent:@"store.data"];
}

- (BOOL)saveChanges {
    //NSString *path = [self itemArchivePath];
    //return [NSKeyedArchiver archiveRootObject:self.privateItems toFile:path];
    NSError *error;
    BOOL successful = [self.context save:&error];
    if (!successful) {
        NSLog(@"Error saving: %@", [error localizedDescription]);
    }
    return successful;
}

- (void)moveItemAtIndex:(NSUInteger)fromIndex toIndex:(NSUInteger)toIndex {
    if (fromIndex == toIndex) {
        return;
    }
    BNRItem *item = self.privateItems[fromIndex];
    [self.privateItems removeObjectAtIndex:fromIndex];
    [self.privateItems insertObject:item atIndex:toIndex];
}

- (void)removeItem:(BNRItem *)item {
    NSString *key = item.itemKey;
    [[BNRImageStore sharedStore] deleteImageForKey:key];
    [self.privateItems removeObjectIdenticalTo:item];
}

- (instancetype)init {
    @throw [NSException exceptionWithName:@"Singleton" reason:@"User + [BNRItemStore sharedStore]" userInfo:nil];
    return nil;
}

- (instancetype)initPrivate {
    self = [super init];
    if (self) {
        // 读取Homepowner.xcdatamodeld
        _model = [NSManagedObjectModel mergedModelFromBundles:nil];
        NSPersistentStoreCoordinator *psc = [[NSPersistentStoreCoordinator alloc] initWithManagedObjectModel:_model];
        //设置SQLite文件路径
        NSString *path = [self itemArchivePath];
        NSURL *storeURL = [NSURL fileURLWithPath: path];
        NSError *error = nil;
        if (![psc addPersistentStoreWithType:NSSQLiteStoreType configuration:nil URL:storeURL options:nil error: &error]) {
            @throw [NSException exceptionWithName:@"OpenFailure" reason:[error localizedDescription] userInfo:nil];
        }
        _context = [[NSManagedObjectContext alloc] init];
        _context.persistentStoreCoordinator = psc;
    }
    return self;
}

- (NSArray *)allItems {
    return self.privateItems;
}

- (void)loadAllItems {
    
}

- (BNRItem *)createItem {
    //BNRItem *item = [BNRItem randomItem];
    BNRItem *item = [[BNRItem alloc] init];
    [self.privateItems addObject:item];
    return item;
}

@end
