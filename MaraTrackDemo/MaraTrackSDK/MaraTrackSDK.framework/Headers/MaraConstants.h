//
//  MaraConstants.h
//  MaraTrackSDK
//
//  Created by pk on 2017/8/7.
//  Copyright © 2017年 com.maramara. All rights reserved.
//

#ifndef MaraConstants_h
#define MaraConstants_h

/// 当前跑步状态
///
/// - notRun:       跑步未开始
/// - run:          正在跑步
/// - autoPaused:   跑步自动暂停
/// - paused:       跑步手动暂停
/// - finished:     跑步结束
/// - error:        错误
typedef NS_ENUM(int32_t, TrackerStatus) {
    TrackerStatusNotRun     = 0,
    TrackerStatusRun        = 1,
    TrackerStatusAutoPaused = 2,
    TrackerStatusPaused     = 3,
    TrackerStatusFinished   = 4,
    TrackerStatusError      = -1,
};



/// 跑步环境
///
/// - outdoor: 户外跑
/// - indoor: 室内跑
typedef NS_ENUM(int32_t, Environment) {
    EnvironmentOutdoor = 1,
    EnvironmentIndoor  = 2,
};

/**
 sdk注册结果

 - SDKRegisterOnlineSuccess: 身份验证通过
 - SDKRegisterOnlineFailure: 身份验证不通过
 */
typedef NS_ENUM(int32_t, SDKRegisterResult) {
    SDKRegisterOnlineSuccess     = 0,
    SDKRegisterOnlineFailure     = 1,
};

#endif /* MaraConstants_h */
