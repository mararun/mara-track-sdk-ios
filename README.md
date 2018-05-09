
MaraTrackSDK 是基于定位开发的快速集成的跑步功能，包含有定位、自动暂停、恢复跑步、记录跑步数据等功能。
本文档记述马拉马拉跑步引擎（下称引擎或Engine）SDK iOS版本（下称SDK）的介绍和集成指引。

## SDK结构
### 整体结构
#### MaraTrackAuth
马拉授权类。向马拉马拉注册您的应用，进行在线或者离线授权。授权成功后方能使用SDK。
#### MaraTrackManager
对Engine进行生命周期管理和初始化。
#### MaraTrackerConfig
封装了初始化引擎时需要使用的配置项。
#### MaraUserLocation
自定义 location 对象，包含当前点（CLLocation）和当前跑步状态。
#### TrackTask
封装了跑步中的基本数据，包含distance、time、pace等基本信息
#### MaraConstants
`TrackerStatus`和`Environment`枚举常量
	
## SDK集成和使用
#### 必要条件：

- 需要开启定位权限
- 需要开启运动与健身权限

(1)

![]	(image/mara-track-sdk-img1.png)

(2)
![]	(image/mara-track-sdk-img2.png)

(3)
由于SDK中使用了扩展，所以需要在工程 - Build Settings - Other Linker Flags中增加-all_load选项。

### 申请授权
有如下三种授权方式：

``` object-c

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

``` 

### 配置文件
`MaraTrackerConfig`封装引擎初始化和配置需要的一些选项，包括：

* `userID` 用户标识，会记录在最终的跑步详情中
* `lapDistance` 每圈距离，单位米，影响`LapInfo`的计算，默认为1000
* `environment` 跑步类型（室外跑`outdoor`、室内跑`indoor`），参看`MaraConstants.Environment `
* `enableAutoPause` 是否开启自动暂停，默认关闭
* `enableDistanceProvision` 是否启用步数补充跑步里程，默认开启
* `enableHA` 是否启用高可靠机制。启用以后引擎会在存储器保存跑步数据。app意外中断后可以恢复跑步，默认开启
* `enableExceptionalPointFilter` 是否开启飘移点过滤，默认开启
* `stepLength` 平均步长，单位米，默认为1
* `debug` 调试信息开关，默认开启

### 使用轨迹管理者
``` object-c
MaraTrackerConfig *config = [[MaraTrackerConfig alloc] init];
    self.trackManager = [[MaraTrackManager alloc] initWith:config locManager:self.locationManager delegate:self];
    [self.trackManager startRun];
```

### 状态控制
Engine的状态转换如下图所示：
![](image/mara-track-sdk-img3.png)

利用上图所示的下列方法对Engine跑步状态进行控制：

``` object-c
/**
 初始化
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

```
 
### 数据获取
利用下列接口同步获取跑步相关数据：

```object-c
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
```

### 状态和数据更新回调

@required

跑步状态改变时的回调函数，时机包括：暂停跑步、恢复跑步、自动暂停、自动恢复跑步。
```
- (void)maraTrackManager:(MaraTrackManager *)manager didUpdateStatus:(TrackerStatus)status;
```

每秒钟的回调函数，读取engine中的实时数据。
```
- (void)maraTrackManager:(MaraTrackManager *)manager didUpdateData:(TrackTask *)task;
```

实时更新定位坐标(GCJ-02坐标系)
```
- (void)maraTrackManager:(MaraTrackManager *)manager didUpdateLocation:(MaraUserLocation *)location;
```

中断恢复跑步时 恢复地图路线
```
- (void)maraTrackManager:(MaraTrackManager *)manager restoreInterruptData:(NSString *)json;
```

@optional

```
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
```

### 跑步详情结构
从Engine获取的跑步详情，格式为json。
其中大多数字段的用途一目了然，下面数据结构进行介绍。

```json
{
	"altitude_up": 0,                             // 海拔总爬升，单位米
	"altitude_down": 62.200000000000003,          // 海拔总下降，单位米
	"avr_pace": 265.53340766565816,               // 平均配速，单位秒
	"avr_step_freq": 3.0218874997147789,          // 平均步频，单位步/秒
	"avr_step_length": 1.2462424460176627,        // 平均步长，单位米
	"cheat_flag": 0,                              // 是否为可疑数据，1为可疑
	"disabled_duration": 0.060811042785644531,    // GPS信号不可用时间，单位秒
	"distance": 11568.868626381962,               // 跑步距离，单位米
	"duration": 3071.9211091995239,               // 跑步时长，单位秒       
	"halted_duration": 573.08153891563416,        // 暂停时间，单位秒
	"init_time": 1501072208,                      // 引擎初始化时间戳，unix epoc time
	"start_time": 1501104372,                     // 跑步开始时间戳，unix epoc time
	"end_time": 1501108017,                       // 跑步完成时间戳，unix epoc time
	"environment": 1,                             // 跑步类型，1为路跑
	"faint_distance": 0,                          // GPS不可用时用计步补充距离，单位米
	"faint_duration": 0,                          // GPS不可用时间，单位秒
	"lapinfo": {
		"lap_detail": [{
			"asc": 0,                             // 圈总爬升，单位米
			"dec": 37.100000000000001,            // 圈总下降，单位米
			"distance": 1000,                     // 圈距离，单位米
			"duration": 263.18735673677486,       // 圈时长，单位秒
			"endpoint": {                         // 圈完结点，经纬度
				"latitude": 39.866745062934029,
				"longitude": 116.50043294270833
			},
			"lap_no": 1,                          // 圈编号
			"pace": 263.18735673677486,           // 圈配速，单位秒
			"start_time": 1501104372.9105909,     // 圈开始时间戳，unix epoc time
			"step_freq": 2.8230839399443743,      // 圈平均步频，单位步/秒
			"step_length": 1.3458950201884252,    // 圈平均步长，单位米
			"step_num": 743                       // 圈总步数
		},
		...,
		"lap_num": 12                             // 总圈数，包括不足一圈距离的最后一圈
	},
	"max_pace": 256.68859662604513,               // 最快配速，单位秒/每圈距离
	"min_pace": 275.99028879037826,               // 最慢配速，单位秒/每圈距离
	"max_altitude": 58.200000000000003,           // 最高海拔，单位米
	"min_altitude": 2.2000000000000002,           // 最低海拔，单位米
	"max_step_freq": 3.2333333333333334,          // 单位时间（1分钟）最大步频，单位步/秒
	"max_step_length": 2.789730014175178,         // 单位时间（1分钟）最大步长，单位米
	"min_step_freq": 0,                           // 单位时间（1分钟）最小步频，单位步/秒
	"min_step_length": 0,                         // 单位时间（1分钟）最小步长，单位米
	"step_info": [{                               // 一个计步单位时间内数据
		"distance": 217.39579980598864,           // 距离，单位米
		"duration": 60,                           // 时长，单位秒
		"seq_no": 0,                              // 数据编号
		"step": 123                               // 总步数
	},
	...
```
	