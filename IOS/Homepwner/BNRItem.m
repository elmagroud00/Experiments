//
//  BNRItem.m
//  Homepwner
//
//  Created by sijiewang on 11/7/15.
//  Copyright © 2015 lnmcc. All rights reserved.
//

#import "BNRItem.h"

@implementation BNRItem

// Insert code here to add functionality to your managed object subclass

- (void)setThumbnail:(UIImage *)image {
    CGSize origImageSize = image.size;
    CGRect newRect = CGRectMake(0, 0, 40, 40);
    float ratio = MAX(newRect.size.width / origImageSize.width, newRect.size.height / origImageSize.height);
    UIGraphicsBeginImageContextWithOptions(newRect.size, NO, 0.0);
    UIBezierPath *path = [UIBezierPath bezierPathWithRoundedRect:newRect cornerRadius:5.0];
    [path addClip];
    CGRect projectionRect;
    projectionRect.size.width = ratio * origImageSize.width;
    projectionRect.size.height = ratio * origImageSize.height;
    projectionRect.origin.x = (newRect.size.width - projectionRect.size.width) / 2;
    projectionRect.origin.y = (newRect.size.height - projectionRect.size.height) / 2;
    [image drawInRect:projectionRect];
    UIImage *smallImage = UIGraphicsGetImageFromCurrentImageContext();
    self.thumbnail = smallImage;
    UIGraphicsEndImageContext();
}

- (void)awakeFromInsert {
    [super awakeFromInsert];
    self.dateCreated = [NSDate date];
    NSUUID *uuid = [[NSUUID alloc] init];
    NSString *key = [uuid UUIDString];
    self.itemKey = key;
}

@end
