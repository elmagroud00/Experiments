//
//  YDViewController.m
//  FotoDownloader
//
//  Created by sijiewang on 12/9/15.
//  Copyright © 2015 lnmcc. All rights reserved.
//

#import "YDViewController.h"

@interface YDViewController () <NSURLConnectionDataDelegate> {
    NSInteger fileSize;
    NSInteger bytesDownload;
}
- (IBAction)startDownload:(UIButton *)sender;
@end

@implementation YDViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view from its nib.
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (IBAction)startDownload:(UIButton *)sender {
    BOOL success;
    NSURL *url;
    NSURLRequest *request;
    url = [NSURL URLWithString:@"http://lnmcc.net/wordpress/wp-content/uploads/2013/11/1276_lines_of_code5.png"];
    success = (url != nil);
    self.filePath = [self createFileName];
    self.fileStream = [NSOutputStream outputStreamToFileAtPath:self.filePath append:NO];
    [self.fileStream open];
    request = [NSURLRequest requestWithURL:url];
    self.connection = [NSURLConnection connectionWithRequest:request delegate:self];
    self.receivedImage.image = nil;
    self.progressView.progress = 0;
}

- (void)stopReceiveWithStatus: (NSString *)statusString {
    if (self.connection != nil) {
        [self.connection cancel];
    }
    if (self.fileStream != nil) {
        [self.fileStream close];
        self.fileStream = nil;
    }
    self.statusLabel.text = statusString;
    self.receivedImage.image = [UIImage imageWithContentsOfFile:self.filePath];
    self.filePath = nil;
}

- (void)connection:(NSURLConnection *)connection didReceiveResponse:(NSURLResponse *)response {
    static NSSet *sSupportedImageTypes;
    NSHTTPURLResponse *httpRespose;
    if (sSupportedImageTypes == nil) {
        sSupportedImageTypes = [[NSSet alloc] initWithObjects:@"image/jpeg", @"image/png", @"image/gif", nil];
    }
    httpRespose = (NSHTTPURLResponse *)response;
    fileSize = [[[httpRespose allHeaderFields] valueForKey:@"Content-Length"] integerValue];
    bytesDownload = 0;
    
    if (httpRespose.statusCode != 200) {
        NSLog(@"error: %@", [NSString stringWithFormat:@"HTTP error %zd", (ssize_t)httpRespose.statusCode]);
    } else {
        NSString *fileMIMEType;
        fileMIMEType = [[httpRespose MIMEType] lowercaseString];
        if (fileMIMEType == nil) {
            [self stopReceiveWithStatus:@"No Content-Type!"];
        } else if (![sSupportedImageTypes containsObject:fileMIMEType]) {
            [self stopReceiveWithStatus:[NSString stringWithFormat:@"Unsupported Content-Type (%@)", fileMIMEType]];
        } else {
            self.statusLabel.text = @"Response OK";
        }
    }
}

- (void)connection:(NSURLConnection *)connection didReceiveData:(NSData *)data {
    NSLog(@"Did ReceiveData. Data length: %d", [data length]);
    NSInteger dataLength;
    const uint8_t *dataBytes;
    NSInteger bytesWritten;
    NSInteger bytesWrittenSoFar;
    dataLength = [data length];
    dataBytes = [data bytes];
    bytesWrittenSoFar = 0;
    
    do {
        bytesWritten = [self.fileStream write:&dataBytes[bytesWrittenSoFar] maxLength:dataLength - bytesWrittenSoFar];
        if (bytesWritten == -1) {
            [self stopReceiveWithStatus:@"File write error"];
            break;
        } else {
            bytesWrittenSoFar += bytesWritten;
        }
        bytesDownload += bytesWritten;
        self.progressView.progress = ((float)bytesDownload / (float)fileSize);
    } while (bytesWrittenSoFar != dataLength);
}

- (void)connection:(NSURLConnection *)connection didFailWithError:(NSError *)error {
    [self stopReceiveWithStatus:@"Connection failed!"];
}

- (void)connectionDidFinishLoading:(NSURLConnection *)connection {
    [self stopReceiveWithStatus:@"downloaded has finished"];
}

- (NSString *)createFileName {
    NSDateFormatter *formatter = [[NSDateFormatter alloc] init];
    [formatter setDateFormat:@"ddmmyyyy-HHmmssSSS"];
    return [NSTemporaryDirectory() stringByAppendingPathComponent:[NSString stringWithFormat:@"%@.png", [formatter stringFromDate:[NSDate date]]]];
}

/*
#pragma mark - Navigation

// In a storyboard-based application, you will often want to do a little preparation before navigation
- (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender {
    // Get the new view controller using [segue destinationViewController].
    // Pass the selected object to the new view controller.
}
*/

@end
