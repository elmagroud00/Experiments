//
//  ViewController.m
//  YDChatApp
//
//  Created by sijiewang on 12/1/15.
//  Copyright © 2015 lnmcc. All rights reserved.
//

#import "ViewController.h"
#import "YDChatUser.h"
#import "YDChatTableView.h"
#import <QuartzCore/QuartzCore.h>
#import "YDChatTableViewDataSource.h"
#import "YDChatData.h"
#import "YDChatUser.h"

#define lineHeight 16.0f

@interface ViewController () <YDChatTableViewDataSource, UITextViewDelegate> {
    
    YDChatTableView *chatTable;
    UIView *textInputView;
    UITextField *textField;
    NSMutableArray *Chats;
    
    UIView *sendView;
    UIButton *sendButton;
    UITextView *msgText;
    BOOL composing;
    float prevLines;
    YDChatUser *me;
    YDChatUser *you;
}

@end

@implementation ViewController

CGRect appFrame;

- (void)viewDidLoad {
    [super viewDidLoad];
    
    self.view.backgroundColor = [UIColor lightGrayColor];
    // create your instance of YDChatTable
    chatTable = [[YDChatTableView alloc] initWithFrame:CGRectMake(0, 40, [[UIScreen mainScreen] bounds].size.width, [[UIScreen mainScreen] bounds].size.height - 40) style:UITableViewStylePlain];
    chatTable.backgroundColor = [UIColor whiteColor];
    [self.view addSubview:chatTable];
    
    appFrame = [[UIScreen mainScreen] applicationFrame];
    
    sendView = [[UIView alloc] initWithFrame:CGRectMake(0, appFrame.size.height - 56, 320, 56)];
    sendView.backgroundColor = [UIColor blueColor];
    sendView.alpha = 0.9;
    
    msgText = [[UITextView alloc] initWithFrame:CGRectMake(7, 10, 225, 36)];
    msgText.backgroundColor = [UIColor blueColor];
    sendView.alpha = 0.9;
    
    msgText = [[UITextView alloc] initWithFrame:CGRectMake(7, 10, 225, 36)];
    msgText.backgroundColor = [UIColor whiteColor];
    msgText.textColor = [UIColor blackColor];
    msgText.font = [UIFont boldSystemFontOfSize:12];
    msgText.autoresizingMask = UIViewAutoresizingFlexibleHeight | UIViewAutoresizingFlexibleTopMargin;
    msgText.layer.cornerRadius = 10.0f;
    msgText.returnKeyType = UIReturnKeySend;
    msgText.showsHorizontalScrollIndicator = NO;
    msgText.showsVerticalScrollIndicator = NO;
    msgText.delegate = self;
    [sendView addSubview:msgText];
    msgText.contentInset = UIEdgeInsetsMake(0, 0, 0, 0);
    [self.view addSubview:sendView];
    
    sendButton = [[UIButton alloc] initWithFrame:CGRectMake(235, 10, 77, 36)];
    sendButton.backgroundColor = [UIColor lightGrayColor];
    [sendButton addTarget:self action:@selector(sendMessage) forControlEvents:UIControlEventTouchUpInside];
    sendButton.autoresizingMask = UIViewAutoresizingFlexibleTopMargin;
    sendButton.layer.cornerRadius = 6.0f;
    [sendButton setTitle:@"Send" forState:UIControlStateNormal];
    [sendView addSubview:sendButton];
    
    me = [[YDChatUser alloc] initWithUsername:@"Peter" avatarImage:[UIImage imageNamed:@"mebubble.png"]];
    you = [[YDChatUser alloc] initWithUsername:@"You" avatarImage:[UIImage imageNamed:@"yoububble.jpg"]];
    YDChatData *first = [YDChatData dataWithText:@"Hey, how are you doing ?" date:[NSDate dateWithTimeIntervalSinceNow: -600] type:ChatTypeMine andUser:me];
    YDChatData *second = [YDChatData dataWithText:@"I am coding !" date:[NSDate dateWithTimeIntervalSinceNow:-600] type:ChatTypeSomeone andUser:you];
    
    [chatTable reloadData];
}

- (void)sendMessage {
    composing = NO;
    YDChatData *thisChat = [YDChatData dataWithText:msgText.text date:[NSDate date] type:ChatTypeMine andUser:me];
    [Chats addObject:thisChat];
    [chatTable reloadData];
    [self showTableView];
    [msgText resignFirstResponder];
    msgText.text = @"";
    sendView.frame = CGRectMake(0, appFrame.size.height - 56, 320, 56);
    NSIndexPath *indexPath = [NSIndexPath indexPathForRow:0 inSection:0];
    [chatTable scrollToRowAtIndexPath:indexPath atScrollPosition:UITableViewScrollPositionBottom animated:YES];
}

#pragma UITextViewDelegate
- (BOOL)textView:(UITextView *)textView shouldChangeTextInRange:(NSRange)range replacementText:(NSString *)text {
    
    if ([text isEqualToString:@"\n"]) {
        [self sendMessage];
        return NO;
    }
    return YES;
}

- (CGFloat)textY {
    UIFont *systemFont = [UIFont boldSystemFontOfSize:12];
    int width = 225.0, height = 10000.0;
    NSMutableDictionary *attrs = [[NSMutableDictionary alloc] init];
    [attrs setObject:systemFont forKey:NSFontAttributeName];
    
    CGRect size = [msgText.text boundingRectWithSize:CGSizeMake(width, height) options:NSStringDrawingUsesLineFragmentOrigin attributes:attrs context:nil];
    float textHeight = size.size.height;
    float lines = textHeight / lineHeight;
    if (lines >= 4) {
        lines = 4;
    }
    if ([msgText.text length] == 0) {
        lines = 0.9375f;
    }
    return 190 - (lines * lineHeight) + lineHeight;
}

- (void)textViewDidChange:(UITextView *)textView {
    UIFont *systemFont = [UIFont boldSystemFontOfSize:12];
    int width = 225.0, height = 10000.0;
    NSMutableDictionary *attrs = [[NSMutableDictionary alloc] init];
    [attrs setObject:systemFont forKey:NSFontAttributeName];
    CGRect size = [msgText.text boundingRectWithSize:CGSizeMake(width, height) options:NSStringDrawingUsesLineFragmentOrigin attributes:attrs context:nil];
    float textHeight = size.size.height;
    float lines = textHeight / lineHeight;
    if (lines >= 4) {
        lines = 4;
    }
    composing = YES;
    msgText.contentInset = UIEdgeInsetsMake(0, 0, 0, 0);
    sendView.frame = CGRectMake(0, appFrame.size.height - 270 - (lines * lineHeight) + lineHeight, 320, 56 + (lines * lineHeight) - lineHeight);
    if (prevLines != lines) {
        [self shortenTableView];
    }
    prevLines = lines;
    
}

- (void)shortenTableView {
    [UIView beginAnimations:@"moveView" context:nil];
    [UIView setAnimationDuration:0.1];
    chatTable.frame = CGRectMake(0, 0, 320, [self textY]);
    [UIView commitAnimations];
}

- (void)showTableView {
    [UIView beginAnimations:@"moveView" context:nil];
    [UIView setAnimationDuration:0.1];
    chatTable.frame = CGRectMake(0, 0, 320, 460 - 56);
    [UIView commitAnimations];
}

- (void)textViewDidBeginEditing:(UITextView *)textView {
    [UIView beginAnimations:@"moveView" context:nil];
    [UIView setAnimationDuration:0.3];
    sendView.frame = CGRectMake(0, appFrame.size.height - 270, 320, 56);
    [UIView commitAnimations];
    [msgText becomeFirstResponder];
}

- (NSInteger)rowsForChatTable:(YDChatTableView *)tableView {
    return [Chats count];
}

- (YDChatData *)chatTableView:(YDChatTableView *)tableView dataForRow:(NSInteger)row {
    return [Chats objectAtIndex:row];
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

@end














