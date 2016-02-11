//
//  RWKnobControl.h
//  KnobControl
//
//  Created by sijiewang on 2/11/16.
//  Copyright © 2016 RayWenderlich. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface RWKnobControl : UIControl

/**
  Contains the current value
 */
@property (nonatomic, assign) CGFloat value;

/**
 Sets the value the knob should represent, with optional animation of thr change.
 */
- (void)setValue:(CGFloat)value animated:(BOOL)animated;

# pragma mark - Vaule Limits
/**
 The minimun value of the knob. Defaults to 0.
 */
@property (nonatomic, assign) CGFloat minimumValue;

/**
 The maximum value of the knob. Defaults to 1.
 */
@property (nonatomic, assign) CGFloat maximumValue;

# pragma mark - Knob Behavior
/**
 Contains a Boolean value indication whether changed in the valure of the knob
 generate continous update events. The default value is 'YES'.
 */
@property (nonatomic, assign, getter=isContinuous) BOOL continuous;

/**
 Specifies the angle of the start of the knob control track. Defaluts to -11PI / 8
 */
@property (nonatomic, assign) CGFloat startAngle;

/**
 Specifies the end angle of the knob control track. Defaults to 3PI / 8
 */
@property (nonatomic, assign) CGFloat endAngle;

/**
 Specifies the width in points of the knob control track. Defaults to 2.0
 */
@property (nonatomic, assign) CGFloat lineWidth;

/**
 Specifies the length in points of the pointer on the knob. Defaults to 6.0
 */
@property (nonatomic, assign) CGFloat pointerLength;

@end
