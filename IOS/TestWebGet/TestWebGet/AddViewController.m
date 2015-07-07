//
//  AddViewController.m
//  TestWebGet
//
//  Created by sijiewang on 7/5/15.
//  Copyright (c) 2015 lnmcc. All rights reserved.
//

#import "AddViewController.h"

@interface AddViewController ()

@end

@implementation AddViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view.
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (void)startRequest {
    NSDate *date = [NSDate new];
    NSDateFormatter *dateFormatter = [[NSDateFormatter alloc]init];
    [dateFormatter setDateFormat:@"yyyy-MM-dd"];
    NSString *dateStr = [dateFormatter stringFromDate:date];
    NSString *post = [NSString stringWithFormat:@"email=%@&type=%@&action=%@&action=%@", @"lnmcc@hotmail.com", @"JSON", @"add", dateStr, _textView.text];
    
    NSString *strURL = [[NSString alloc]initWithFormat:@"http://iosbook1.com/service/mynote/webservice.php"];
    NSURL *url = [NSURL URLWithString:[strURL URLEncodedString]];
    NSData *postData = [post dataUsingEncoding:NSUTF8StringEncoding];
    
    NSMutableURLRequest *request = [NSMutableURLRequest requestWithURL:url];
    [request setHTTPMethod:@"POST"];
    [request setHTTPBody:postData];
    
    NSURLConnection *connection = [[NSURLConnection alloc]initWithRequest:request delegate:self];
    
    if (connection) {
        _datas = [NSMutableData new];
    }
}

- (viod)viewWillAppear:(BOOL)animated {
    [super viewWillAppear:YES];
    [self startRequest];
}

#pragma mark- NSURLConnection回调
- (void)connection:(NSURLConnection*)connection didReceiveData:(NSData *)data {
    [_datas appendData:data];
}

- (void)connection:(NSURLConnection *)connection didFailWithError:(NSError *)error {
    NSLog(@"%@", [error localizedDescription]);
}

- (void)connectionDidFinishLoading:(NSURLConnection *)connection {
    NSLog(@"请求完成...");
    NSDictionary *dict = [NSJSONSerialization JSONObjectWithData:_datas options:NSJSONReadingAllowFragments error:nil];
    NSString *message = @"操作成功";
    NSNumber *resultCodeObj = [dict objectForKey:@"ResultCode"];
    if ([resultCodeObj integerValue] < 0) {
        //message = [resultCodeObj er]
    }
    UIAlertView *alertView = [[UIAlertView alloc]initWithTitle:@"提示信息" message:message delegate:nil cancelButtonTitle:@"OK" otherButtonTitles:nil];
    [alertView show];
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
