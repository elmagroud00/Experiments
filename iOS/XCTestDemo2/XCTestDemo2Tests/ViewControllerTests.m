//
//  ViewControllerTests.m
//  XCTestDemo2
//
//  Created by sijiewang on 3/18/16.
//  Copyright © 2016 lnmcc. All rights reserved.
//

#import <XCTest/XCTest.h>
#import "ViewController+Test.h"

@interface ViewControllerTests : XCTestCase

@property (nonatomic) ViewController *vcToTest;

@end

@implementation ViewControllerTests

- (void)setUp {
    [super setUp];
    self.vcToTest = [[ViewController alloc] init];
}

- (void)tearDown {
    // Put teardown code here. This method is called after the invocation of each test method in the class.
    [super tearDown];
}

- (void)testStringOutput {
    NSString *wantedString = @"wangsijie";
    NSString *outputString = [self.vcToTest stringOutput];
    XCTAssertEqualObjects(outputString, wantedString, @"The result is error");
}

@end
