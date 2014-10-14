//
//  main.m
//  Rectagle
//
//  Created by sijiewang on 9/9/14.
//  Copyright (c) 2014 lnmcc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "Rectagle.h"

int main(int argc, const char * argv[])
{

    @autoreleasepool {
        Rectagle *myRectagle = [[Rectagle alloc]init];
        [myRectagle setWidth:5 andHeight: 8];
        NSLog(@"Rectagle: w = %i, h = %i", myRectagle.width, myRectagle.height);
        NSLog(@"Area = %i, perimeter = %i", [myRectagle area], [myRectagle perimeter]);
    }
    return 0;
}

