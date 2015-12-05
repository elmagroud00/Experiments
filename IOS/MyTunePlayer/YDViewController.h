//
//  YDViewController.h
//  MyTunePlayer
//
//  Created by sijiewang on 12/5/15.
//  Copyright © 2015 lnmcc. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <MediaPlayer/MediaPlayer.h>

@interface YDViewController : UIViewController

@property (weak, nonatomic) IBOutlet UITableView *mTableView;
@property (nonatomic, strong) NSMutableArray *allItems;
@property (nonatomic, strong) MPMusicPlayerController *musicPlayer;

@end
