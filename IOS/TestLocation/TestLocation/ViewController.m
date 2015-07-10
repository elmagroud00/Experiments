//
//  ViewController.m
//  TestLocation
//
//  Created by sijiewang on 7/7/15.
//  Copyright (c) 2015 lnmcc. All rights reserved.
//

#import "ViewController.h"
#import <AddressBook/AddressBook.h>

@interface ViewController ()

@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view, typically from a nib.
    _locationManager = [[CLLocationManager alloc]init];
    _locationManager.delegate = self;
    _locationManager.desiredAccuracy = kCLLocationAccuracyBest;
    _locationManager.distanceFilter = 100.0f;
}

- (void)viewWillAppear:(BOOL)animated {
    [super viewWillAppear:animated];
    [_locationManager startUpdatingLocation];
}

-(void)viewWillDisappear:(BOOL)animated {
    [super viewWillDisappear:animated];
    [_locationManager stopUpdatingLocation];
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

-(void)locationManager:(CLLocationManager *)manager didUpdateLocations:(NSArray *)locations {
    CLLocation *currLocation = [locations lastObject];
    _txtLat.text = [NSString stringWithFormat:@"%3.5f", currLocation.coordinate.latitude];
    _txtLng.text=[NSString stringWithFormat:@"%3.5f", currLocation.coordinate.longitude];
    _txtAlt.text = [NSString stringWithFormat:@"%3.5f", currLocation.altitude];
}

-(void)locationManager:(CLLocationManager *)manager didFailWithError:(NSError *)error {
    NSLog(@"error: %@", error);
}

- (IBAction)geocodeQuery:(UIButton *)sender {
    if (_txtQueryKey.text == nil || [_txtQueryKey.text length] == 0) {
        return;
    }
    
    CLGeocoder *geocoder = [[CLGeocoder alloc]init];
    [geocoder geocodeAddressString:_txtQueryKey.text completionHandler:^(NSArray *placemarks, NSError *error) {
        if ([placemarks count] > 0) {
            CLPlacemark *placemark = [placemarks objectAtIndex:0];
            CLLocationCoordinate2D coordinate = placemark.location.coordinate;
            NSDictionary *addressDictionary = placemark.addressDictionary;
            NSString *address = [addressDictionary objectForKey:(NSString*)kABPersonAddressStreetKey];
            address = address == nil ? @"" : address;
            NSString *city = [addressDictionary objectForKey:(NSString*)kABPersonAddressCityKey];
            city = city == nil ? @"" : city;
            
            _txtView.text = [NSString stringWithFormat:@"%@", city];
            [_txtQueryKey resignFirstResponder];
        }
    }];
}
@end
