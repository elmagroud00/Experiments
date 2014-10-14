//
//  Rectagle.m
//  Rectagle
//
//  Created by sijiewang on 9/9/14.
//  Copyright (c) 2014 lnmcc. All rights reserved.
//

#import "Rectagle.h"

@implementation Rectagle
@synthesize width, height;
-(void) setWidth:(int)w andHeight:(int)h
{
    width = w;
    height = h;
}
-(int) area
{
    return width * height;
}
-(int) perimeter
{
    return (width + height) * 2;
}
@end
