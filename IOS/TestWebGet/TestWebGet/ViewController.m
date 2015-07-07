//
//  ViewController.m
//  TestWebGet
//
//  Created by sijiewang on 7/4/15.
//  Copyright (c) 2015 lnmcc. All rights reserved.
//

#import "ViewController.h"

@interface ViewController ()

@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view, typically from a nib.
    self.navigationItem.leftBarButtonItem = self.editButtonItem;
    [self startRequest];
}

-(void)startRequest {
    NSString *strURL = [[NSString alloc]initWithFormat:@"http://lnmcc.net"];
    NSURL *url = [NSURL URLWithString:[strURL URLEncodedString]];
    NSLog(@"URL Encoded = %@",[strURL URLEncodedString]);
    NSURLRequest *request = [[NSURLRequest alloc]initWithURL:url];
    NSURLConnection *connection = [[NSURLConnection alloc] initWithRequest:request delegate:self];
    
    if (connection) {
        _datas = [NSMutableData new];
    }
}

#pragma mark- NSURLConnection回调方法
-(void)connection:(NSURLConnection*)connection didReceiveData:(NSData *)data {
    [_datas appendData:data];
    //NSLog(@"Received Data: %s", data);
}

-(void)connection:(NSURLConnection *)connection didFailWithError:(NSError *)error {
    NSLog(@"%@", [error localizedDescription]);
}

-(void)connectionDidFinishLoading:(NSURLConnection *)connection {
    NSLog(@"请求完成...");
    NSDictionary *dict = [NSJSONSerialization JSONObjectWithData:_datas options:NSJSONReadingAllowFragments error:nil];
    [self reloadView:dict];
}


#pragma mark - Table View
- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView {
    return 1;
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section {
    return self.listData.count;
}

- (UITableViewCell*)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {
    
    static NSString *CELL_TAG = @"Cell";
    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:CELL_TAG forIndexPath:indexPath];
    NSMutableDictionary* dict = self.listData[indexPath.row];
    cell.textLabel.text = [dict objectForKey:@"Content"];
    cell.detailTextLabel.text = [dict objectForKey:@"CData"];
    
    return cell;
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

@end
