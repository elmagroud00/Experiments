//
//  YDViewController.m
//  VideoRecoder
//
//  Created by sijiewang on 12/9/15.
//  Copyright © 2015 lnmcc. All rights reserved.
//

#import "YDViewController.h"
#import <MobileCoreServices/MobileCoreServices.h>

@interface YDViewController () <UIImagePickerControllerDelegate>
- (IBAction)recordVideo:(UIButton *)sender;
@end

@implementation YDViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view from its nib.
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (IBAction)recordVideo:(UIButton *)sender {
    if ([UIImagePickerController isSourceTypeAvailable:UIImagePickerControllerSourceTypeCamera]) {
        self.camera = [[UIImagePickerController alloc] init];
        self.camera.sourceType = UIImagePickerControllerSourceTypeCamera;
        self.camera.mediaTypes = [[NSArray alloc] initWithObjects:(NSString *)kUTTypeMovie, nil];
        self.camera.showsCameraControls = YES;
        self.camera.delegate = self;
        [self presentViewController:self.camera animated:YES completion:nil];
    } else {
        UIAlertView *alert = [[UIAlertView alloc] initWithTitle:@"Error" message:@"No camera avaiable" delegate:nil cancelButtonTitle:@"OK" otherButtonTitles:nil, nil];
        [alert show];
    }
}

#pragma mark UIImagePickerController delegate
- (void)imagePickerController:(UIImagePickerController *)picker didFinishPickingMediaWithInfo:(NSDictionary<NSString *,id> *)info {
    NSString *mediaType = [info objectForKey:UIImagePickerControllerMediaType];
    [self dismissViewControllerAnimated:YES completion:nil];
    if (CFStringCompare((CFStringRef)mediaType, kUTTypeMovie, 0) == kCFCompareEqualTo) {
        NSString *moviePath = (NSString *)[[info objectForKey:UIImagePickerControllerMediaURL] path];
        if (UIVideoAtPathIsCompatibleWithSavedPhotosAlbum(moviePath)) {
            UISaveVideoAtPathToSavedPhotosAlbum(moviePath, self, @selector(video:didFinishSavingWithError:contextInfo:), nil);
        }
    }
}

- (void)video: (NSString *)videoPath didFinishSavingWithError: (NSError *)error contextInfo: (void *)contextInfo {
    if (error) {
        UIAlertView *alert = [[UIAlertView alloc] initWithTitle:@"Error" message:@"Video Saving Failed" delegate:nil cancelButtonTitle:@"OK" otherButtonTitles:nil, nil];
        [alert show];
    } else {
        UIAlertView *alert = [[UIAlertView alloc] initWithTitle:@"Video Saved" message:@"Saved to your Photo Alblum" delegate:self cancelButtonTitle:@"OK" otherButtonTitles:nil, nil];
        [alert show];
    }
}

/*
#pragma mark - Navigation

// In a storyboard-based application, you will often want to do a little preparation before navigation
- (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender {
    // Get the new view controller using [segue destinationViewController].
    // Pass the selected object to the new view controller.
}
*/

@end
