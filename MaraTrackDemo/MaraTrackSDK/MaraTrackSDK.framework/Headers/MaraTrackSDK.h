//
//  MaraTrackSDK.h
//  MaraTrackSDK
//
//  Created by pk on 2017/8/2.
//  Copyright © 2017年 com.maramara. All rights reserved.
//


#import <MaraTrackSDK/MaraTrackManager.h>
#import <MaraTrackSDK/MaraTrackerConfig.h>
#import <MaraTrackSDK/MaraUserLocation.h>
#import <MaraTrackSDK/TrackTask.h>
#import <MaraTrackSDK/MaraConstants.h>
#import <MaraTrackSDK/MaraLocationManager.h>


@interface MaraTrackSDK : NSObject

+ (MaraTrackSDK*)shared;

/**
 向马拉马拉注册第三方应用

 @param appKey Mara分配的唯一标识
 @param block 回调
 */
- (void)registerApp:(NSString *)appKey block: (void (^)(SDKRegisterResult))block;

@end
