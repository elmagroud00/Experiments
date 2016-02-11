#import "MediaControl.h"

@implementation MediaControl 

- (void)load {
    UIView *view = [[[NSBundle bundleForClass:[self class]] loadNibNamed:@"MediaControl" owner:self options:nil] firstObject];
    view.frame = self.frame;

    [self addSubview:view];
    //[self updateConstraints];
}

- (id)initWithFrame:(CGRect)frame {
    self = [super initWithFrame:frame];
    if (self) {
        [self load];
    }
    return self;
}

- (void)awakeFromNib {
    [super awakeFromNib];
}

#pragma mark IBAction

@end
