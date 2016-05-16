//
//  Persion.h
//  TestKVC
//
//  Created by sijiewang on 5/15/16.
//  Copyright © 2016 lnmcc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "Account.h"

@interface Person : NSObject {
    @private
    int _age;
}

#pragma mark - 属性
#pragma mark 姓名
@property (nonatomic, copy) NSString *name;
#pragma mark 账户
@property (nonatomic, strong) Account *account;

#pragma mark - 公共方法
#pragma mark 显示人员信息
-(void)showMessage;
@end
