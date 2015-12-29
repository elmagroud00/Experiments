//
//  URLRequest.m
//  WebsiteUsingBlock
//
//  Created by sijiewang on 12/10/15.
//  Copyright © 2015 lnmcc. All rights reserved.
//

#import "URLRequest.h"

@interface URLRequest() <NSURLConnectionDataDelegate> {
    NSURLRequest *request;
    NSURLConnection *connection;
    NSMutableData *webData;
    int httpStatusCode;
    void (^completion)(URLRequest *request, NSData *data, BOOL success);
}
@end

@implementation URLRequest

- (instancetype)initWithRequest:(NSURLRequest *)req {
    self = [super init];
    if (self != nil) {
        request = req;
    }
    return self;
}

- (void)startWithCompletion:(void(^)(URLRequest*, NSData *, BOOL))compl {
    completion = [compl copy];
    connection = [[NSURLConnection alloc] initWithRequest:request delegate:self];
    if (connection) {
#if !__has_feature(objc_arc)
        webData = [[NSMutableData alloc] retain];
#else
        webData = [[NSMutableData alloc] init];
#endif
        //completion(self, webData, YES);
    } else {
        completion(self, nil, NO);
    }
}

#if !__has_feature(objc_arc)
- (void)dealloc {
    if (webData != nil)
        [webData release];
    if (connection != nil)
        [connection release];
    
    [super dealloc];
}
#endif

- (void)connectionDidFinishLoading:(NSURLConnection *)connection {
    completion(self, webData, httpStatusCode == 200);
}

- (void)connection:(NSURLConnection *)connection didReceiveResponse:(NSURLResponse *)response {
    NSHTTPURLResponse *httpResponse = (NSHTTPURLResponse *)response;
    httpStatusCode = [httpResponse statusCode];
    [webData setLength:0];
}

- (void)connection:(NSURLConnection *)connection didReceiveData:(NSData *)data {
    [webData appendData:data];
}

- (void)connection:(NSURLConnection *)connection didFailWithError:(NSError *)error {
    completion(self, webData, NO);
}

@end













