//
//  ViewController.m
//  MaraTrackDemo
//
//  Created by pk on 2017/8/8.
//  Copyright © 2017年 com.maramara. All rights reserved.
//

#import "ViewController.h"
#import <MaraTrackSDK/MaraTrackAuth.h>
#import "RunViewController.h"
#import "SAMKeychain.h"

static NSString* kAppKey = @"0YZUdPpywBZCQox78ybkQPjJzPqibaN8UT6lj9TjtCbuIrE6LupbJhWbeLoONFml";

@interface ViewController ()
@property (nonatomic, strong) MaraLocationManager *locManager;
@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];

    MaraLocationManager * loctionManager = [[MaraLocationManager alloc] init];
    self.locManager = loctionManager;
    
    [self checkTrackStatus];
}

- (void)checkTrackStatus {
    NSString *deviceID = [self deviceID];
    [[MaraTrackAuth shared] registerApp:kAppKey deviceID:deviceID block:^(SDKRegisterResult result) {
        NSLog(@"%s %d", __func__, (int)result);
        if (result == SDKRegisterResultSuccess) {
            MaraTrackerConfig *config = [[MaraTrackerConfig alloc] init];
            // 这里只是得到跑步状态，所以参数locManager和delegate传nil
            MaraTrackManager *manager = [[MaraTrackManager alloc] initWith:config locManager:nil delegate:nil];
            TrackerStatus status = [manager getRunStatus];
            if (status != TrackerStatusError && status != TrackerStatusNotRun) {
                // 恢复
                [self.locManager startUpdatingLocation];

                RunViewController *runVC = [[RunViewController alloc] init];
                runVC.locationManager = self.locManager;
                [self.navigationController pushViewController:runVC animated:YES];
            }
        }
    }];
}

- (NSString*)deviceID {
    NSString *account = @"DeviceIDAccount";
    NSString *service = @"DeviceIDService";
    
    NSString *deviceID = [SAMKeychain passwordForService:service account:account];
    if (deviceID == nil) {
        deviceID = [[[UIDevice currentDevice] identifierForVendor] UUIDString];
        [SAMKeychain setPassword:deviceID forService:service account:account];
    }
    return deviceID;
}

- (IBAction)startRunBtnDidClicked:(id)sender {
    [self.locManager startUpdatingLocation];
    
    RunViewController *runVC = [[RunViewController alloc] init];
    runVC.locationManager = self.locManager;
    [self.navigationController pushViewController:runVC animated:YES];
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
}


@end
