//
//  Persion.m
//  TestKVC
//
//  Created by sijiewang on 5/15/16.
//  Copyright © 2016 lnmcc. All rights reserved.
//

#import "Person.h"

@implementation Person

#pragma mark - 公共方法
#pragma mark 显示人员信息
-(void)showMessage {
    NSLog(@"name=%@, age=%d", _name, _age);
}

#pragma mark 设置人员账户
-(void)setAccount:(Account *)account {
    _account = account;
    [self.account addObserver:self forKeyPath:@"balance" options:NSKeyValueObservingOptionNew context:nil];
}

#pragma mark - 覆盖方法
#pragma mark 重写observeValueForKeyPath
-(void)observeValueForKeyPath:(NSString *)keyPath ofObject:(id)object change:(NSDictionary<NSString *,id> *)change context:(void *)context {
    if ([keyPath isEqualToString:@"balance"]) {
        NSLog(@"keyPath = %@, object = %@, newValue = %.2f, context = %@", keyPath, object, [[change objectForKey:NSKeyValueChangeNewKey] floatValue], context);
    }
}

#pragma mark 重写销毁方法
-(void)dealloc {
    [self.account removeObserver:self forKeyPath:@"balance"];
}

@end
