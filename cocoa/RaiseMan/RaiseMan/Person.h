//
//  Person.h
//  RaiseMan
//
//  Created by sijiewang on 10/27/14.
//  Copyright (c) 2014 lnmcc. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface Person : NSObject
{
    NSString *personName;
    float expectedRaise;
}
@property(readwrite, copy)NSString *personName;
@property(readwrite, assign)float expectedRaise;
@end
