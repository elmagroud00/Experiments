//
//  RWKnobControl.m
//  KnobControl
//
//  Created by sijiewang on 2/11/16.
//  Copyright © 2016 RayWenderlich. All rights reserved.
//

#import "RWKnobControl.h"
#import "RWKnobRenderer.h"
<<<<<<< HEAD
#import "RWRotationGestureRecognizer.h"

@implementation RWKnobControl {
    RWKnobRenderer *_knobRenderer;
    RWRotationGestureRecognizer *_gestureRecognizer;
=======

@implementation RWKnobControl {
    RWKnobRenderer *_knobRenderer;
>>>>>>> deac650587f5c64b62d9f550d803d37f4fc6d2cd
}

@dynamic lineWidth;
@dynamic startAngle;
@dynamic endAngle;
@dynamic pointerLength;

- (instancetype)initWithFrame:(CGRect)frame {
    self = [super initWithFrame:frame];
    if (self) {
        // Initialization code
        //self.backgroundColor = [UIColor blueColor];
        
        _minimumValue = 0.0;
        _maximumValue = 1.0;
        _value = 0.0;
        _continuous = YES;
<<<<<<< HEAD
        _gestureRecognizer = [[RWRotationGestureRecognizer alloc] initWithTarget:self action:@selector(handleGesture:)];
        [self addGestureRecognizer:_gestureRecognizer];
=======
>>>>>>> deac650587f5c64b62d9f550d803d37f4fc6d2cd
        [self createKnobUI];
    }
    return self;
}

#pragma mark - API Method
- (void)setValue:(CGFloat)value animated:(BOOL)animated {
    if (value != _value) {
        [self willChangeValueForKey:@"value"];
        // Save the value to the backing ivar
        // Make sure we limit it to the requested bounds
        _value = MIN(self.maximumValue, MAX(self.minimumValue, value));
        // Now lets update the knob with the correct angle
        CGFloat angleRange = self.endAngle - self.startAngle;
        CGFloat valueRange = self.maximumValue - self.minimumValue;
        CGFloat angleForValue = (_value - self.maximumValue) / valueRange * angleRange + self.startAngle;
        [_knobRenderer setPointerAngle:angleForValue animate:animated];
        [self didChangeValueForKey:@"value"];
    }
}

#pragma mark - Property overrides
- (void)setValue:(CGFloat)value {
    // Chain with the animation method version
    [self setValue:value animated:NO];
}

- (void)createKnobUI {
    _knobRenderer = [[RWKnobRenderer alloc] init];
    [_knobRenderer updateWithBounds:self.bounds];
    _knobRenderer.color = self.tintColor;
    _knobRenderer.startAngle = -M_PI * 11 / 8.0;
    _knobRenderer.endAngle = M_PI * 3 / 8.0;
    _knobRenderer.pointerAngle = _knobRenderer.startAngle;
    _knobRenderer.lineWidth = 2.0;
    _knobRenderer.pointerLength = 6.0;
    [self.layer addSublayer:_knobRenderer.trackLayer];
    [self.layer addSublayer:_knobRenderer.pointerLayer];
}

- (CGFloat)lineWidth {
    return _knobRenderer.lineWidth;
}

- (void)setLineWidth:(CGFloat)lineWidth {
    _knobRenderer.lineWidth = lineWidth;
}

- (CGFloat)startAngle {
    return _knobRenderer.startAngle;
}

- (void)setStartAngle:(CGFloat)startAngle {
    _knobRenderer.startAngle = startAngle;
}

- (CGFloat)endAngle {
    return _knobRenderer.endAngle;
}

- (void)setEndAngle:(CGFloat)endAngle {
    _knobRenderer.endAngle = endAngle;
}

- (CGFloat)pointerLength {
    return _knobRenderer.pointerLength;
}

- (void)setPointerLength:(CGFloat)pointerLength {
    _knobRenderer.pointerLength = pointerLength;
}

- (void)tintColorDidChange {
    _knobRenderer.color = self.tintColor;
}

+ (BOOL) automaticallyNotifiesObserversForKey:(NSString *)key {
    if ([key isEqualToString:@"value"]) {
        return NO;
    } else {
        return [super automaticallyNotifiesObserversForKey:key];
    }
}

<<<<<<< HEAD
- (void)handleGesture:(RWRotationGestureRecognizer *)gesture {
    // 1. Mid-point angle
    CGFloat midPointAngle = (2 * M_PI + self.startAngle - self.endAngle) / 2 + self.endAngle;
    // 2. Ensure the angle is within a suitable range
    CGFloat boundedAngle = gesture.touchAngle;
    if (boundedAngle > midPointAngle) {
        boundedAngle -= 2 * M_PI;
    } else if (boundedAngle < (midPointAngle - 2 * M_PI)) {
        boundedAngle += 2 * M_PI;
    }
    // 3. Bound the angle to within the suitable range
    boundedAngle = MIN(self.endAngle, MAX(self.startAngle, boundedAngle));
    
    // 4. Convert the angle to a value
    CGFloat angleRange = self.endAngle - self.startAngle;
    CGFloat valueRange = self.maximumValue -self.minimumValue;
    CGFloat valueForAngle = (boundedAngle - self.startAngle) / angleRange * valueRange + self.minimumValue;
    
    // 5. Set the control to this value
    self.value = valueForAngle;
    
    if (self.continuous) {
        [self sendActionsForControlEvents:UIControlEventValueChanged];
    } else {
        // Only send an update if the gesture has completed
        if (_gestureRecognizer.state == UIGestureRecognizerStateEnded ||
            _gestureRecognizer.state == UIGestureRecognizerStateCancelled) {
            [self sendActionsForControlEvents:UIControlEventValueChanged];
        }
    }
}

=======
>>>>>>> deac650587f5c64b62d9f550d803d37f4fc6d2cd
/*
// Only override drawRect: if you perform custom drawing.
// An empty implementation adversely affects performance during animation.
- (void)drawRect:(CGRect)rect {
    // Drawing code
}
*/

@end
