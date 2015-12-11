//
//  URLRequest.h
//  WebsiteUsingBlock
//
//  Created by sijiewang on 12/10/15.
//  Copyright © 2015 lnmcc. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface URLRequest : NSObject
- (instancetype)initWithRequest: (NSURLRequest *)req;
- (void)startWithCompletion:(void(^)(URLRequest*, NSData *, BOOL))compl;
@end
