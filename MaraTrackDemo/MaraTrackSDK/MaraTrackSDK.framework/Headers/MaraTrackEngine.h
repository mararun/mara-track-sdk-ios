//
//  MaraTrackEngine.h
//  MaraTrackSDK
//
//  Created by pk on 2017/8/2.
//  Copyright © 2017年 com.maramara. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreLocation/CoreLocation.h>
#import "MaraConstants.h"

/**
 sdk注册结果
 
 - EngineRegisterOnlinePassed: 在线身份验证通过
 - EngineRegisterOnlineFailed: 在线身份验证不通过
 - EngineRegisterOfflinePassed: 离线身份验证通过
 - EngineRegisterOfflineFailed: 离线身份验证不通过
 - EngineRegisterError: 发生错误
 */
typedef NS_ENUM(int32_t, EngineRegisterResult) {
    EngineRegisterOnlinePassed     = 0,
    EngineRegisterOnlineFailed     = 1,
    EngineRegisterOfflinePassed    = 2,
    EngineRegisterOfflineFailed    = 3,
    EngineRegisterError            = -1,
};

@interface MaraTrackEngine : NSObject

/**
 得到App认证URL

 @param bundleID bundleID
 @param appKey appKey
 @return 认证URL
 */
- (NSString*)getAuthenticationURI: (NSString*)bundleID appKey: (NSString*)appKey;

/**
 得到认证结果

 @param encryptedStr 加密字符串
 @param filePath 文件路径
 @return 认证结果
 */
- (EngineRegisterResult)maraGetAuthenticationResult: (NSString*)encryptedStr filePath: (NSString*)filePath;

/**
 Engine init

 @param userID 用户id 默认用uuid
 @param sessionID 会话id，用于唯一确定一个需要记录的跑步过程。
 @param lapDist 一圈的长度
 @param path  数据文件的路径
 */
- (BOOL)createTrackWithUserID:(NSString *)userID sessionID:(uint64_t)sessionID lapDist:(int64_t)lapDist filePath:(NSString *)path;

/**
 关闭引擎

 @param delfile delfile 是否删除数据文件 0 不删除，1 删除
 */
- (void)mr_closeTracker:(int32_t)delfile;

/**
 设置调试模式

 @param mode           0 关闭调试模式。此模式下不会在设备上存储tracker的调试信息。
                       1 打开调试模式。此模式下会在设备商保存调试信息供开发人员分析。
 @return 0  成功 -1 失败。
 */
- (int32_t)mr_setDebugMode:(int8_t)mode;

/**
 设置自动暂停

 @param flag     0 关闭自动暂停，1 开启自动暂停
 @return 0  成功 -1 失败。
 */
- (int32_t)mr_setAutoPause:(int32_t)flag;

/**
 设置跑步类型

 @param mode 1 路跑 2 室内跑
 @return 0 成功
 */
- (int32_t)mr_setEnvironmentMode:(uint64_t)mode;

/**
 获取跑步类型
 */
- (int32_t)mr_maraEnvironment;

/*  maraSetSelectMode
 *  功能：设置下次调用maraRunnerLocUpdate传入坐标点时是否将新产生的里程和时间计入总的时间和里程
 *   mode      是否累计新产生的里程和时间。0 累计， 1 不累计。
 */
- (int32_t)mr_maraSetSelectMode:(uint32_t)mode;

/**
 获取当前跑步状态
 */
- (int32_t)mr_maraGetTrackerStatus;

/**
 开始跑步
 */
- (int32_t)mr_maraStartRunning;

/**
 停止跑步
 */
- (int32_t)mr_maraStopRunning;

/**
 手动暂停
 */
- (int32_t)mr_maraAttemptPause;

/**
 继续跑步
 */
- (int32_t)mr_maraResumeTracker;

/**
 更新跑步者坐标

 @return 0  成功 -1 失败。
 */
- (int32_t)mr_maraRunnerLocUpdate:(CLLocationDegrees)lon latitude:(CLLocationDegrees)lat altitude:(CLLocationDistance)altitude;

/**
 步数更新（调用一次代表一步）

 @return 0  成功 -1 失败。
 */
- (int32_t)mr_maraRunnerStepUpdate;

/**
 更新tracker状态

 @return 0  成功 -1 失败。
 */
- (int32_t)mr_maraRunnerTimeUpdate;

/**
 总距离 米
 */
- (double)mr_maraGetCurrentDistance;

/**
 总用时 秒
 */
- (double)mr_maraGetCurrentDuration;

/**
 当前速度 m/s
 */
- (double)mr_maraGetCurrentSpeed;

/**
 当前海拔 米
 */
- (double)mr_maraGetCurrentAltitude;

/**
 当前海拔总上升 米
 */
- (double)mr_maraGetCurrentAltitudeUp;

/**
 当前海拔总下降 米
 */
- (double)mr_maraGetCurrentAltitudeDown;

/**
 当前圈海拔上升 米
 */
- (double)mr_maraGetCurLapAltitudeUp;

/**
 当前圈海拔下降 米
 */
- (double)mr_maraGetCurLapAltitudeDown;

/**
 平均配速 s/m
 */
- (double)mr_maraGetAvrPace;

/**
 当前圈配速 s/m
 */
- (double)mr_maraGetCurLapPace;

/**
 平均步频 秒/步
 */
- (double)mr_maraGetAvrStepFreq;

/**
 平均步长 米
 */
- (double)mr_maraGetAvrStepDistance;

/**
 总暂停时间
 */
- (double)mr_maraGetHaltDuration;

/**
 以跑圈数
 */
- (int32_t)mr_maraGetCurLapNum;

/**
 当前圈已跑里程 米
 */
- (double)mr_maraGetCurLapDistance;

/**
 当前圈 总用时 秒
 */
- (double)mr_maraGetCurLapDuration;

/**
 获取整个跑步过程的tracker信息
 */
- (NSString *)mr_maraGetTrackerInfo;


/**
 获取错误信息
 */
- (NSString *)mr_maraGetErrorMsg;

/**
 获取上一次调用maraRunnerLocUpdate或maraRunnerTimeUpdate接口的时间

 @return >0 UNIX时间戳 -1 失败
 */
- (int64_t)mr_maraGetLastUpdateTime;

/**
 是否开启飘逸点过滤
 */
- (int32_t)mr_setExceptionalPointFilter:(BOOL)enable;

/*  maraSetConfig
 *  功能：调整tracker的一些属性值
 *  输入参数:
 *            ctx   已初始化的上下文数据结构
 *            key   1 海拔计算阈值。大于此值的海拔升降才会被计入海拔总上升下降。默认值1米
 *                  2 自动暂停速度阈值。默认值0.5米/秒
 *                  3 自动暂停时间阈值。默认值5秒
 *                  4 中断时间阈值。如果新的点与上一个点之间的时间差超过此阈值，则认为此期间设备宕机，这段时间和距离不累计。默认值30
 *                  5 用于判断自动恢复跑步的最大速度差。默认值3
 *                  6 最大瞬时速度阈值。默认值10米/秒。（需要通过maraSetDenoiseMode打开ENABLE_SINGLE_POINT_SPEED_CHECK生效）
 *                  7 最大瞬时加速度阈值。默认值3米/秒^2。（需要通过maraSetDenoiseMode打开ENABLE_SINGLE_POINT_SPEED_CHECK生效）
 *                  8 计步器模式开启阈值。默认值0秒。
 *                  9 初始步长。用于计步器模式下的里程计算。默认值1米
 *
 *            value 设置值
 *  返回值：
 *            0  成功
 * */
- (int32_t)mr_setConfig:(int)key value:(int)value;

/**
 传入心率

 @param hr 当前秒的心率
 */
- (BOOL)mr_hrUpdate: (int)hr;
@end
