//
//  Rectagle.h
//  Rectagle
//
//  Created by sijiewang on 9/9/14.
//  Copyright (c) 2014 lnmcc. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface Rectagle : NSObject
{
    int width;
    int height;
}
@property int width, height;
-(void) setWidth:(int)width andHeight:(int) height;
-(int) area;
-(int) perimeter;
@end
