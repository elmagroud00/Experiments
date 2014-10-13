//
//  main.m
//  AddressCard
//
//  Created by sijiewang on 10/12/14.
//  Copyright (c) 2014 lnmcc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <Foundation/NSObject.h>
#import <Foundation/NSString.h>
#import <Foundation/NSArray.h>


@interface AddressCard : NSObject
{
    NSString *name;
    NSString *email;
}
@property (copy, nonatomic) NSString *name, *email;

- (void) print;
- (void) setName: (NSString*) theName andEmail: (NSString*) theEmail;
@end

@implementation AddressCard
@synthesize name, email;

- (void) print
{
    NSLog(@"====================================");
    NSLog(@"%-31s|", [name UTF8String]);
    NSLog(@"%-31s|", [email UTF8String]);
    NSLog(@"");
    NSLog(@"");
    NSLog(@"");
    NSLog(@"O O|");
    NSLog(@"====================================");
}

- (void) setName:(NSString *)theName andEmail:(NSString *)theEmail
{
    self.name = theName;
    self.email = theEmail;
}
@end



@interface AddressBook : NSObject
{
    NSString *bookName;
    NSMutableArray *book;
}
-(id)initWithName : (NSString*)name;
-(void)addCard : (AddressCard*)theCard;
-(int)entries;
-(void)list;
-(void)dealloc;
@end

@implementation AddressBook
-(id)initWithName:(NSString *)name
{
    self = [super init];
    if(self) {
        bookName = [[NSString alloc]initWithString:name];
        book = [[NSMutableArray alloc]init];
    }
    return self;
}

-(void)addCard:(AddressCard *)theCard
{
    [book addObject:theCard];
}

-(int)entries
{
    return [book count];
}

-(void)list
{
    NSLog(@"==========Contents of : %@==========", bookName);
    for(AddressCard *theCard in book)
        NSLog(@"%-20s%-32s", [theCard.name UTF8String], [theCard.email UTF8String]);
    NSLog(@"====================");
}

-(void)dealloc
{
    [bookName release];
    [book release];
    [super dealloc];
}
@end

int main(int argc, const char * argv[]) {
    @autoreleasepool {
        NSString *aName = @"Julia Kochan";
        NSString *aEmail = @"Julia@hotmail.com";
        AddressCard *card1 = [[AddressCard alloc]init];
        //[card1 setName:aName];
        //[card1 setEmail:aEmail];
        [card1 setName:aName andEmail:aEmail];
        [card1 print];
    }
    return 0;
}
