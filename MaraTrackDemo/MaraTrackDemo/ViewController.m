//
//  ViewController.m
//  MaraTrackDemo
//
//  Created by pk on 2017/8/8.
//  Copyright © 2017年 pk. All rights reserved.
//

#import "ViewController.h"
#import <MaraTrackSDK/MaraTrackSDK.h>
#import "RunViewController.h"

static NSString* kAppKey = @"0YZUdPpywBZCQox78ybkQPjJzPqibaN8UT6lj9TjtCbuIrE6LupbJhWbeLoONFml";

@interface ViewController ()

@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];

    [self checkTrackStatus];
}

- (void)checkTrackStatus {
    [[MaraTrackSDK shared] registerApp:kAppKey block:^(SDKRegisterResult result) {
        NSLog(@"%s %d", __func__, (int)result);
        if (result == SDKRegisterOnlineSuccess) {
            MaraTrackerConfig *config = [[MaraTrackerConfig alloc] init];
            MaraTrackManager *manager = [[MaraTrackManager alloc] initWith:config delegate:nil];
            TrackerStatus status = [manager getRunStatus];
            if (status != TrackerStatusError && status != TrackerStatusNotRun) {
                // 恢复
                RunViewController *runVC = [[RunViewController alloc] init];
                [self.navigationController pushViewController:runVC animated:YES];
            }
        }
    }];
}

- (IBAction)startRunBtnDidClicked:(id)sender {
    RunViewController *runVC = [[RunViewController alloc] init];
    [self.navigationController pushViewController:runVC animated:YES];
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];

}


@end
