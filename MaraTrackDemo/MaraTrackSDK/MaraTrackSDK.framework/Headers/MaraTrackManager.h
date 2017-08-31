//
//  MaraTrackManager.h
//  MaraTrackSDK
//
//  Created by pk on 2017/8/7.
//  Copyright © 2017年 com.maramara. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <MaraTrackSDK/TrackTask.h>
#import <MaraTrackSDK/MaraConstants.h>
#import <MaraTrackSDK/MaraUserLocation.h>
#import <MaraTrackSDK/MaraTrackerConfig.h>

MRT_START_NONNULL

@class MaraTrackManager;

@protocol MaraTrackManagerDelegate <NSObject>
@required
/// 每1s 抓取一次engine里的数据更新
- (void)maraTrackManager:(MaraTrackManager *)manager didUpdateData:(TrackTask *)task;

/// 监听当前跑步状态(包含自动暂停和自动恢复)
- (void)maraTrackManager:(MaraTrackManager *)manager didUpdateStatus:(TrackerStatus)status;

/// 实时更新定位坐标(GCJ-02坐标系)
- (void)maraTrackManager:(MaraTrackManager *)manager didUpdateLocation:(MaraUserLocation *)location;

/// 中断恢复跑步时 恢复地图路线
- (void)maraTrackManager:(MaraTrackManager *)manager restoreInterruptData:(NSString *)json;

@end

@interface MaraTrackManager : NSObject

@property (nonatomic, strong, nullable) MaraUserLocation *userLocation;
@property (nonatomic, strong, nullable) TrackTask *trackTask;
/**
 初始化方法

 @param config 配置
 @param delegate 代理
 @return 对象
 */
- (instancetype)initWith:(MaraTrackerConfig *)config delegate:(id<MaraTrackManagerDelegate> _Nullable)delegate;

/**
 开始跑步
 */
- (BOOL)startRun;

/**
 手动暂停跑步
 */
- (BOOL)pauseRun;

/**
 继续跑步
 */
- (BOOL)resumeRun;

/**
 结束本次跑步
 */
- (BOOL)stopRun;

#pragma mark -- 数据

/**
 * 获取当前跑步距离
 * @return 距离，单位米
 */
- (double)getDistance;

/**
 * 获取平均配速
 * @return 配速，单位秒
 */
- (double)getAveragePace;

/**
 * 获取当圈配速
 * @return 配速，单位秒
 */
- (double)getLapPace;

/**
 * 获取当前跑步时长
 * @return 时长，单位秒
 */
- (double)getDuration;

/**
 * 获取暂停时长
 * @return 时长，单位秒
 */
- (double)getHaltDuration;

/**
 * 获取当前海拔
 * @return 海拔，单位米
 */
- (double)getAltitude;

/**
 * 获取总爬升
 * @return 爬升，单位米
 */
- (double)getTotalAscend;

/**
 * 获取总下降
 * @return 下降，单位米
 */
- (double)getTotalDescend;

/**
 * 获取当圈爬升
 * @return 爬升，单位米
 */
- (double)getLapAscend;

/**
 * 获取当圈下降
 * @return 下降，单位米
 */
- (double)getLapDescend;

/**
 * 获取平均步频
 * @return 平均步频，单位步/分钟
 */
- (double)getAverageCadence;

/**
 * 获取跑步详细数据，具体格式信息请参考文档
 * @return 跑步详细数据，格式为json
 */
- (NSString *)getRunDetailJson;

/**
 * 获取数据最后一次更新时间
 * @return 时间，为unix时间戳
 */
- (long long)getLastUpdateTime;

/**
 * 获取跑步模式
 * @return 模式，室内 or 路跑
 */
- (Environment)getRunEnvironment;

/**
 * 获取跑步状态
 * @return 状态
 */
- (TrackerStatus)getRunStatus;

@end

MRT_END_NONNULL
