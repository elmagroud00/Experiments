//
//  BNRItemCell.m
//  Homepwner
//
//  Created by sijiewang on 10/1/15.
//  Copyright © 2015 lnmcc. All rights reserved.
//

#import "BNRItemCell.h"

@implementation BNRItemCell

-(IBAction)showImage:(id)sender {
    if (self.actionBlock) {
        self.actionBlock();
    }
}

@end


