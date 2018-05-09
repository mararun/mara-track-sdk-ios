//
//  MaraTrackManager.h
//  MaraTrackSDK
//
//  Created by pk on 2017/8/7.
//  Copyright © 2017年 com.maramara. All rights reserved.
//
//  整理 Yalin 2018/05/09

#import <Foundation/Foundation.h>
#import <MaraTrackSDK/TrackTask.h>
#import <MaraTrackSDK/MaraConstants.h>
#import <MaraTrackSDK/MaraUserLocation.h>
#import <MaraTrackSDK/MaraTrackerConfig.h>
#import <MaraTrackSDK/MaraTrackError.h>
#import <MaraTrackSDK/MaraTrackerRecordUploadManager.h>

MRT_START_NONNULL

@class MaraTrackManager;
@class MaraLocationManager;

@protocol MaraTrackManagerDelegate <NSObject>

@required
/// 跑步状态改变时的回调函数，时机包括：暂停跑步、恢复跑步、自动暂停、自动恢复跑步。
- (void)maraTrackManager:(MaraTrackManager *)manager didUpdateStatus:(TrackerStatus)status;

/// 每秒钟的回调函数，读取engine中的实时数据。
- (void)maraTrackManager:(MaraTrackManager *)manager didUpdateData:(TrackTask *)task;

/// 实时更新定位坐标(GCJ-02坐标系)
- (void)maraTrackManager:(MaraTrackManager *)manager didUpdateLocation:(MaraUserLocation *)location;

/// 中断恢复跑步时 恢复地图路线
- (void)maraTrackManager:(MaraTrackManager *)manager restoreInterruptData:(NSString *)json;

@optional
/**
 跑步记录文件上传结果通知

 @param manager 轨迹管理者
 @param success 是否上传成功
 @param data 服务端返回的数据
 @param filePath 上传跑步记录文件的本地路径
 @param statusCode 服务端返回的HTTP状态码
 */
- (void)maraTrackManager: (MaraTrackManager*)manager recordUploadResult: (BOOL)success data: (NSData*)data filePath: (NSString*)filePath code: (NSInteger)statusCode;

/**
 错误回调

 @param manager 轨迹管理者
 @param error 错误
 @param detail 错误详情
 @param data 错误详情中的附加数值型信息
 */
- (void)maraTrackManager:(MaraTrackManager *)manager error:(MaraTrackError)error detail:(NSString*)detail data:(int)data;
@end

@interface MaraTrackManager : NSObject

@property (nonatomic, strong, nullable) MaraUserLocation *userLocation;
@property (nonatomic, strong, nullable) TrackTask *trackTask;

/**
 初始化方法
 @param config 配置
 @param manager 定位对象
 @param delegate 代理
 @return 对象
 */
- (instancetype)initWith:(MaraTrackerConfig *)config locManager:(MaraLocationManager * _Nullable)manager delegate:(id<MaraTrackManagerDelegate> _Nullable)delegate;

/**
 开始跑步

 @return YES：成功；NO：失败
 */
- (BOOL)startRun;

/**
 手动暂停跑步

 @return YES：成功；NO：失败
 */
- (BOOL)pauseRun;

/**
 继续跑步

 @return YES：成功；NO：失败
 */
- (BOOL)resumeRun;

/**
 结束跑步

 @return MaraTrackErrorNoError：成功。
 可能的错误有：MaraTrackErrorStopRunning，MaraTrackErrorGetTrackInfo，MaraTrackErrorSaveTrack。
 */
- (MaraTrackError)stopRun;

/**
 上传单条跑步跑步记录

 @param filePath 指定跑步记录的地址
 @param bizUserID 用户业务ID
 @return 是否正确进行了上传。NO:参数不正确或者正在上传中，此次没有发送上传请求。
 */
- (RecordUploadResult)uploadOneRecord: (NSString*)filePath extraData: (NSString*)extraData bizUserID: (NSString*)bizUserID;

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

/**
 每秒钟调用，传入心率

 @param hr 当前秒的心率值
 */
- (BOOL)hrDataUpdate: (int)hr;

@end

MRT_END_NONNULL
