//
//  YDFirstViewController.m
//  Guestbook
//
//  Created by sijiewang on 12/21/15.
//  Copyright © 2015 lnmcc. All rights reserved.
//

#import "YDFirstViewController.h"
#import "URLRequest.h"

@interface YDFirstViewController () <UITableViewDataSource, UITableViewDelegate>

@end

@implementation YDFirstViewController

- (instancetype)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil {
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        self.title = NSLocalizedString(@"Table", @"Table");
    }
    return self;
}

- (void)viewDidLoad {
    [self.mTableView setDelegate:self];
    [self.mTableView setDataSource:self];
    [super viewDidLoad];
    [self loadGuestBook];

}

- (void)viewDidAppear:(BOOL)animated {
    [self loadGuestBook];
}

- (void)loadGuestBook {
    if (self.postion != nil) {
        self.postion = nil;
    }
    NSURL *myUrl = [NSURL URLWithString:@"http://api.douban.com/labs/bubbler/user/ahbei"];
    NSMutableURLRequest *request = [NSMutableURLRequest requestWithURL:myUrl cachePolicy:NSURLRequestReloadIgnoringLocalCacheData timeoutInterval:10];
    // import to the Content-Type to application/json to receive JSON format response
    [request setValue:@"application/json" forHTTPHeaderField:@"Content-Type"];
    URLRequest *urlRequest = [[URLRequest alloc] initWithRequest:request];
    [urlRequest startWithCompletion:^(URLRequest *request, NSData *data, BOOL success) {
        if (success) {
            NSLog(@"Get data: %@", [[NSString alloc] initWithData:data encoding:NSUTF8StringEncoding]);
            NSError *error = nil;
            self.postion = [NSJSONSerialization JSONObjectWithData:data options:kNilOptions error:&error];
            if (error) {
                NSLog(@"Error: %@", [error localizedDescription]);
            }
            
            [self.mTableView reloadData];
        } else {
            NSLog(@"Error");
        }
    }];
}

#pragma mark UITableview delegates
- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView {
    return 1;
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section {
    return [self.postion count];
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {
    static NSString *CellIdentifier = @"Cell";
    UITableViewCell *cell = (UITableViewCell *)[tableView dequeueReusableCellWithIdentifier:CellIdentifier];
    if (cell == nil) {
        cell = [[UITableViewCell alloc] initWithStyle:UITableViewCellStyleDefault reuseIdentifier:CellIdentifier];
    }
    
    NSLog(@"Index row = %li", (long)indexPath.row);
    
    //NSDictionary *posting = [self.postion objectAtIndex:indexPath.row];
    cell.selectionStyle = UITableViewCellStyleDefault;
    cell.textLabel.text = [NSString stringWithFormat:@"%@-%@", [self.postion objectForKey:@"id"], [self.postion objectForKey:@"homepage"]];
    return cell;
}

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath {
    [tableView deselectRowAtIndexPath:indexPath animated:YES];
    //NSDictionary *posting = [self.postion objectForKey:@"id"];
    UIAlertView *alert = [[UIAlertView alloc] initWithTitle:[self.postion objectForKey:@"id"] message:[self.postion objectForKey:@"homepage"] delegate:self cancelButtonTitle:@"OK" otherButtonTitles:nil, nil];
    [alert show];
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
