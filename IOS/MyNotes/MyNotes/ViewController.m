//
//  ViewController.m
//  MyNotes
//
//  Created by sijiewang on 6/13/15.
//  Copyright (c) 2015 lnmcc. All rights reserved.
//

#import "ViewController.h"
#import "NoteDetailViewController.h"

@interface ViewController ()

@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view, typically from a nib.
    self.tableView.delegate = self;
    self.tableView.dataSource = self;
    self.title = @"所有日记";
    
    noteBL = [[NoteBL alloc] init];
    notes = [[NSArray alloc] initWithArray:[noteBL findAll]];
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender {
    
    if ([segue.identifier isEqualToString:@"showDetail"]) {
        NSLog(@"prepareForSegue:sender: %@", self.description);
        NoteDetailViewController *detailControl = segue.destinationViewController;
        detailControl.title = currentNote.date.description;
        
        
        if ([detailControl respondsToSelector:@selector(setData:)]) {
            [detailControl setValue:currentNote.content forKey:@"data"];
        }
        //[detailControl setText:@"Hello, are you OK!"];
        //detailControl.noteDetail.text = @"This is a test";//currentNote.content;
    }

}

- (void)tableView:tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath {
    
    NSLog(@"%ld", (long)indexPath.row);
    NSUInteger row = [indexPath row];
    currentNote = [notes objectAtIndex:row];
    [self performSegueWithIdentifier:@"showDetail" sender:self];
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section {
    return [notes count];
}

- (UITableViewCell*)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {
    static NSString *CellIdentifier = @"NoteCell";
    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:CellIdentifier forIndexPath:indexPath];
    
    if (cell == nil) {
        cell = [[UITableViewCell alloc] initWithStyle:UITableViewCellStyleDefault reuseIdentifier:CellIdentifier];
    }
    
    NSUInteger row = [indexPath row];
    currentNote = [notes objectAtIndex:row];
    
    cell.textLabel.text = currentNote.content;
    cell.accessoryType = UITableViewCellAccessoryDisclosureIndicator;
    
    return cell;
}

@end
