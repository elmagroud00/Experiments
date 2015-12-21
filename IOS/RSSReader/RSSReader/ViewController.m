//
//  ViewController.m
//  RSSReader
//
//  Created by sijiewang on 12/21/15.
//  Copyright © 2015 lnmcc. All rights reserved.
//

#import "ViewController.h"
#import "URLRequest.h"

@interface ViewController () <UITableViewDataSource, UITableViewDelegate, NSXMLParserDelegate> {
    NSXMLParser *rssParser;
    NSMutableArray *articles;
    NSMutableDictionary *item;
    NSString *currentElement;
    NSMutableString *ElementValue;
    BOOL errorParsing;
}
@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    [self parseXMLFileAtURL:@"http://rss.nytimes.com/services/xml/rss/nyt/HomePage.xml"];
    [_mTableView setDataSource:self];
}

#pragma mark UITableView delegates
- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView {
    return 1;
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section {
    return [articles count];
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {
    static NSString *CellIdentifier = @"Cell";
    UITableViewCell *cell = (UITableViewCell *)[tableView dequeueReusableCellWithIdentifier:CellIdentifier];
    if (cell == nil) {
        cell = [[UITableViewCell alloc] initWithStyle:UITableViewCellStyleDefault reuseIdentifier:CellIdentifier];
    }
    NSDictionary *feedItem = [articles objectAtIndex:indexPath.row];
    cell.selectionStyle = UITableViewCellSelectionStyleNone;
    cell.textLabel.text = [feedItem objectForKey:@"title"];
    return cell;
}

#pragma mark XML Parsing
- (void)parseXMLFileAtURL:(NSString *)URL {
    NSMutableURLRequest *request = [NSMutableURLRequest requestWithURL:[NSURL URLWithString:URL]];
    URLRequest *urlRequest = [[URLRequest alloc] initWithRequest:request];
    [urlRequest startWithCompletion:^(URLRequest *request, NSData *data, BOOL success) {
        if (success) {
            NSLog(@"Get Data: %@", [[NSString alloc] initWithData:data encoding:NSUTF8StringEncoding]);
            // create the article array
            articles = [[NSMutableArray alloc] init];
            errorParsing = NO;
            // create the NSXMLParser and initialize it with the data received
            rssParser = [[NSXMLParser alloc] initWithData:data];
            // set the delegate
            [rssParser setDelegate:self];
            // You may need to turn some of these on depending on the type of XML file you are parsing
            [rssParser setShouldProcessNamespaces:NO];
            [rssParser setShouldReportNamespacePrefixes:NO];
            [rssParser setShouldResolveExternalEntities:NO];
            [rssParser parse];
        } else {
            NSLog(@"error %@", [[NSString alloc] initWithData:data encoding:NSUTF8StringEncoding]);
        }
    }];
}

- (void)parser:(NSXMLParser *)parser foundCharacters:(nonnull NSString *)string {
    [ElementValue appendString:string];
}

- (void)parser:(NSXMLParser *)parser didEndElement:(nonnull NSString *)elementName namespaceURI:(nullable NSString *)namespaceURI qualifiedName:(nullable NSString *)qName {
    if ([elementName isEqualToString:@"item"]) {
        [articles addObject:[item copy]];
        [self.mTableView reloadData];
    } else {
        [item setObject:ElementValue forKey:elementName];
    }
}

- (void)parserDidStartDocument:(NSXMLParser *)parser {
    
}

- (void)parser:(NSXMLParser *)parser didStartElement:(nonnull NSString *)elementName namespaceURI:(nullable NSString *)namespaceURI qualifiedName:(nullable NSString *)qName attributes:(nonnull NSDictionary<NSString *,NSString *> *)attributeDict {
    currentElement = [elementName copy];
    ElementValue = [[NSMutableString alloc] init];
    if ([elementName isEqualToString:@"item"]) {
        item = [[NSMutableDictionary alloc] init];
    }
}


// This method is called if an error occurs
- (void)parser:(NSXMLParser *)parser parseErrorOccurred:(NSError *)parseError {
    NSString *errorString = [NSString stringWithFormat:@"Error code %li", (long)[parseError code]];
    NSLog(@"Error parsing XML: %@", errorString);
    errorParsing = YES;
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

@end
