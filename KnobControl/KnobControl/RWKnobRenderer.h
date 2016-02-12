//
//  RWKnobRenderer.h
//  KnobControl
//
//  Created by sijiewang on 2/11/16.
//  Copyright © 2016 RayWenderlich. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface RWKnobRenderer : NSObject

#pragma mark - Properties associated with all parts of the renderer
@property (nonatomic, strong) UIColor *color;
@property (nonatomic, assign) CGFloat lineWidth;

#pragma mark - Properites associated with the backgourd track
@property (nonatomic, readonly, strong) CAShapeLayer *trackLayer;
@property (nonatomic, assign) CGFloat startAngle;
@property (nonatomic, assign) CGFloat endAngle;

#pragma mark - Properites associated with the pointer element
@property (nonatomic, readonly, strong) CAShapeLayer *pointerLayer;
@property (nonatomic, assign) CGFloat pointerAngle;
@property (nonatomic, assign) CGFloat pointerLength;

- (void)updateWithBounds:(CGRect)bounds;
- (void)setPointerAngle:(CGFloat)pointerAngle animate:(BOOL)animated;

@end
