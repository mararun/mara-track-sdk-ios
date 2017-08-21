//
//  TrackTask.h
//  MaraTrackSDK
//
//  Created by pk on 2017/8/7.
//  Copyright © 2017年 pk. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface TrackTask : NSObject

/// 距离 （单位：米）
@property (nonatomic) double distance;

/// 时间 （单位：秒）
@property (nonatomic) double time;

/// 平均配速 （单位：米每秒）
@property (nonatomic) double avrPace;

/// 当前配速 （单位：米每秒）
@property (nonatomic) double curPace;

/// 当前海拔 （单位：米）
@property (nonatomic) double altitude;

/// 海拔爬升 （单位：米）
@property (nonatomic) double altitudeUp;

/// 海拔降低 （单位：米）
@property (nonatomic) double altitudeDown;

@end
