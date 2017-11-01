//
//  ViewController.m
//  MaraTrackDemo
//
//  Created by pk on 2017/8/8.
//  Copyright © 2017年 com.maramara. All rights reserved.
//

#import "ViewController.h"
#import <MaraTrackSDK/MaraTrackSDK.h>
#import "RunViewController.h"

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
    [[MaraTrackSDK shared] registerApp:kAppKey block:^(SDKRegisterResult result) {
        NSLog(@"%s %d", __func__, (int)result);
        if (result == SDKRegisterOnlineSuccess) {
            MaraTrackerConfig *config = [[MaraTrackerConfig alloc] init];
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
