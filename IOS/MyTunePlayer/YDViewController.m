//
//  YDViewController.m
//  MyTunePlayer
//
//  Created by sijiewang on 12/5/15.
//  Copyright © 2015 lnmcc. All rights reserved.
//

#import "YDViewController.h"

@interface YDViewController () <UITableViewDataSource, UITableViewDelegate>

@end

@implementation YDViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    self.musicPlayer = [MPMusicPlayerController applicationMusicPlayer];
    [self loadMedia];
    [self.mTableView setDataSource:self];
    [self.mTableView setDelegate:self];
}

- (void)loadMedia {
    // query all songs
    MPMediaQuery *allSongQuery = [[MPMediaQuery alloc] init];
    NSLog(@"All Songs: %@ :", [allSongQuery items]);
    self.allItems = [[NSMutableArray alloc] initWithArray:[allSongQuery items]];
    [self dumpSongs];
    [self.mTableView reloadData];
}

- (void)dumpSongs {
    if (self.allItems != nil && [self.allItems count] > 0) {
        NSLog(@"There are(is) %lu song(s)", (unsigned long)[self.allItems count]);
        for (int i = 0; i < [self.allItems count]; i++) {
            MPMediaItem *item = [self.allItems objectAtIndex:i];
            NSNumber *persistentID = [item valueForProperty:MPMediaItemPropertyArtistPersistentID];
            NSLog(@"PersistentID: %@", persistentID);
        }
    }
}

#pragma mark TableView Delegate
- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView {
    return 1;
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section {
    return [self.allItems count];
}

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath {
    [self.musicPlayer stop];
    [self.musicPlayer setQueueWithItemCollection:nil];
    MPMediaItem *item = [[self.allItems objectAtIndex:[indexPath row]] representativeItem];
    MPMediaPropertyPredicate *myPredicate = [MPMediaPropertyPredicate predicateWithValue:[item valueForProperty:MPMediaItemPropertyAlbumPersistentID] forProperty:MPMediaItemPropertyAlbumPersistentID comparisonType:MPMediaPredicateComparisonContains];
    MPMediaQuery *songsQuery = [MPMediaQuery songsQuery];
    [songsQuery addFilterPredicate:myPredicate];
    // setQuery direct to Queue
    [self.musicPlayer setQueueWithQuery:songsQuery];
    [self.musicPlayer prepareToPlay];
    [self.musicPlayer play];
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {
    NSString *cellIndentifier = @"MyCellIndentifer";
    UITableViewCell *cell = (UITableViewCell *)[tableView dequeueReusableCellWithIdentifier:cellIndentifier];
    if (cell == nil) {
        cell = [[UITableViewCell alloc] initWithStyle:UITableViewCellStyleDefault reuseIdentifier:cellIndentifier];
    }
    MPMediaItem *item = [[self.allItems objectAtIndex:indexPath.row] representativeItem];
    MPMediaItemArtwork *artwork = [item valueForProperty:MPMediaItemPropertyArtwork];
    if (artwork) {
        cell.imageView.image = [artwork imageWithSize:CGSizeMake(30, 30)];
    }
    cell.textLabel.text = [item valueForProperty:MPMediaItemPropertyTitle];
    
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
