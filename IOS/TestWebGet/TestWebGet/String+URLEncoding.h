//
//  String+URLEncoding.h
//  TestWebGet
//
//  Created by sijiewang on 7/4/15.
//  Copyright (c) 2015 lnmcc. All rights reserved.
//

#import <CoreFoundation/CoreFoundation.h>
#import <Foundation/Foundation.h>

@interface NSString (URLEncoding)

-(NSString*)URLEncodedString;
-(NSString*)URLDecodedString;

@end
