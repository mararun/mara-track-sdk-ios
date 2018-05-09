//
//  MaraTrackAuth.h
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
#import <MaraTrackSDK/MaraTrackManager_Ext.h>
#import <MaraTrackSDK/MaraTrackEngine.h>

@interface MaraTrackAuth : NSObject

+ (MaraTrackAuth*)shared;

+ (MaraTrackEngine*)engine;

/**
 向马拉马拉注册第三方应用。首先进行在线授权，失败的情况下进行离线授权。

 @param appKey Mara分配的唯一标识
 @param deviceID 设备ID
 @param block 回调
 */
- (void)registerApp: (NSString*)appKey deviceID: (NSString*)deviceID block: (void (^)(SDKRegisterResult))block;


/**
 首先在线授权，失败后尝试离线授权。

 @param appKey key
 @param block 在线授权或者离线授权的回调
 */
- (void)onlineAuthorization: (NSString*)appKey block: (void (^)(SDKRegisterResult))block;

/**
 首先离线授权，失败后尝试在线授权（在线授权失败后停止，不会继续离线授权）

 @param appKey key
 @param block 在线授权回调
 @return 离线授权结果
 */
- (SDKRegisterResult)offlineAuthorization: (NSString*)appKey block: (void (^)(SDKRegisterResult))block;

@end
