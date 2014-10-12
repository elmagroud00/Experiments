//
//  Square.m
//  Rectagle
//
//  Created by sijiewang on 9/9/14.
//  Copyright (c) 2014 lnmcc. All rights reserved.
//

#import "Square.h"

@implementation Square
-(void) setSide:(int)s
{
    [self setWidth:s andHeight:s];
}
-(int) side
{
    return width;
}
@end
