//
//  MaraTrackerConfig.h
//  MaraTrackSDK
//
//  Created by pk on 2017/8/2.
//  Copyright © 2017年 pk. All rights reserved.
//

#if __has_feature(nullability)
#define MRT_START_NONNULL _Pragma("clang assume_nonnull begin")
#define MRT_END_NONNULL _Pragma("clang assume_nonnull end")
#else
#define MRT_START_NONNULL
#define MRT_END_NONNULL
#endif

#import <Foundation/Foundation.h>
#import <MaraTrackSDK/MaraConstants.h>

/*! @brief
 *  基本参数配置
 */
@interface MaraTrackerConfig : NSObject

/**
 跑步者标识 默认 UUIDString
 */
@property (nonatomic, copy) NSString *userID;

/**
 每圈距离 米，默认1000
 */
@property (nonatomic) int lapDistance;

/**
 跑步类型Environment  默认室外跑
 */
@property (nonatomic) Environment environment;

/**
 是否自动暂停 默认NO
 */
@property (nonatomic) BOOL enableAutoPause;

/**
 是否启用步数补充跑步里程 默认YES
 */
@property (nonatomic) BOOL enableDistanceProvision;

/**
 是否启用高可靠机制EnableHA。启用以后引擎会在存储器保存跑步数据。app意外中断后可以恢复跑步 默认YES
 */
@property (nonatomic) BOOL enableHA;

/**
 是否开启飘移点过滤 默认YES
 */
@property (nonatomic) BOOL enableExceptionalPointFilter;

/**
 Debug信息开关, 默认开启
 */
@property (nonatomic) BOOL debug;

@end
