//
//  MaraUserLocation.h
//  MaraTrackSDK
//
//  Created by pk on 2017/8/7.
//  Copyright © 2017年 com.maramara. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreLocation/CoreLocation.h>
#import <MaraTrackSDK/MaraConstants.h>

@interface MaraUserLocation : NSObject

/**
 最新的坐标点
 */
@property (nullable,nonatomic, strong) CLLocation *location;

/**
 是否进入了计步器模式
 */
@property (nonatomic) BOOL isEnterPedometerType;

/**
 当前状态
 */
@property (nonatomic) TrackerStatus runStatus;

- (BOOL)checkLocationUpdated;

@end
