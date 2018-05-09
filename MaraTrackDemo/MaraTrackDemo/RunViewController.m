//
//  RunViewController.m
//  MaraTrackDemo
//
//  Created by pk on 2017/8/8.
//  Copyright © 2017年 com.maramara. All rights reserved.
//

#import "RunViewController.h"
#import "Utils.h"

@interface RunViewController ()<MaraTrackManagerDelegate>

@property (weak, nonatomic) IBOutlet UILabel *distLabel;
@property (weak, nonatomic) IBOutlet UILabel *avrPaceLabel;
@property (weak, nonatomic) IBOutlet UILabel *curPaceLabel;
@property (weak, nonatomic) IBOutlet UILabel *durationLabel;
@property (weak, nonatomic) IBOutlet UIButton *startPauseBtn;
@property (weak, nonatomic) IBOutlet UILabel *statusLabel;

@property (nonatomic, strong) MaraTrackManager *trackManager;
@property (nonatomic, strong) TrackTask *tipsTask;
@end

@implementation RunViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    [self.navigationController setNavigationBarHidden:YES];
    MaraTrackerConfig *config = [[MaraTrackerConfig alloc] init];
    self.trackManager = [[MaraTrackManager alloc] initWith:config locManager:self.locationManager delegate:self];
    [self.trackManager startRun];
}

- (void)setTipsTask:(TrackTask *)tipsTask {
    _tipsTask = tipsTask;
    self.distLabel.text = [NSString stringWithFormat:@"%0.2f", floor(tipsTask.distance/10)/100];
    self.durationLabel.text = [Utils formatTime:tipsTask.time];
    self.avrPaceLabel.text = [Utils formatSpeed:tipsTask.avrPace];
    self.curPaceLabel.text = [Utils formatSpeed:tipsTask.curPace];
}
- (IBAction)startOrPauseDidClicked:(UIButton *)sender {
    // true 继续, false 暂停
    if (sender.isSelected) {
        [self.trackManager resumeRun];
    } else {
        [self.trackManager pauseRun];
    }
    [sender setSelected:!sender.isSelected];
}
- (IBAction)stopDidClicked:(UIButton *)sender {
    [self.trackManager stopRun];
    NSString *trackInfo = [self.trackManager getRunDetailJson];
    NSLog(@"trackInfo = %@", trackInfo);
    [self.navigationController popViewControllerAnimated:YES];
}

#pragma mark -- MaraTrackManagerDelegate

- (void)maraTrackManager:(MaraTrackManager *)manager didUpdateData:(TrackTask *)task {
    self.tipsTask = task;
}

- (void)maraTrackManager:(MaraTrackManager *)manager didUpdateStatus:(TrackerStatus)status {
    if (status == TrackerStatusAutoPaused) {
        self.statusLabel.text = @"自动暂停";
    } else if (status == TrackerStatusPaused) {
        self.statusLabel.text = @"手动暂停";
    } else if (status == TrackerStatusRun) {
        self.statusLabel.text = @"跑步中";
    }
}

- (void)maraTrackManager:(MaraTrackManager *)manager didUpdateLocation:(MaraUserLocation *)location {

}

- (void)maraTrackManager:(MaraTrackManager *)manager restoreInterruptData:(NSString *)json {
    [self.startPauseBtn setSelected:YES];
    self.statusLabel.text = @"恢复跑步,点击继续";
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];

}

@end
