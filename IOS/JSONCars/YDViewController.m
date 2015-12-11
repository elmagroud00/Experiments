//
//  YDViewController.m
//  JSONCars
//
//  Created by sijiewang on 12/11/15.
//  Copyright © 2015 lnmcc. All rights reserved.
//

#import "YDViewController.h"
#import "URLRequest.h"

@interface YDViewController () <UITableViewDataSource>

@end

@implementation YDViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    [self.mTableView setDataSource:self];
    NSURL *myURL = [NSURL URLWithString:@"https://api.github.com/users/mralexgray/repos"];
    NSMutableURLRequest *request = [NSMutableURLRequest requestWithURL:myURL cachePolicy:NSURLRequestReloadIgnoringLocalCacheData timeoutInterval:60];
    [request setValue:@"application/json" forHTTPHeaderField:@"Content-Type"];
    URLRequest *urlRequest = [[URLRequest alloc] initWithRequest:request];
    [urlRequest startWithCompletion:^(URLRequest *request, NSData *data, BOOL success) {
        if (success) {
            NSError *error = nil;
            self.cars = [NSJSONSerialization JSONObjectWithData:data options:kNilOptions error:&error];
            //NSLog(@"Data: %@", self.cars);
            [self.mTableView reloadData];
        } else {
            NSLog(@"error %@", [[NSString alloc] initWithData:data encoding:NSUTF8StringEncoding]);
        }
    }];
    
}

#pragma UITableView delegates
- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView {
    return  1;
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section {
    return [self.cars count];
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {
    static NSString *CellIdentifier = @"Cell";
    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:CellIdentifier];
    if (cell == nil) {
        cell = [[UITableViewCell alloc] initWithStyle:UITableViewCellStyleDefault reuseIdentifier:CellIdentifier];
    }
    NSDictionary *car = [self.cars objectAtIndex:indexPath.row];
    NSLog(@"car: %@", car);
    cell.selectionStyle = UITableViewCellSelectionStyleBlue;
    cell.textLabel.text = [car objectForKey:@"name"];
    return cell;
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
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







