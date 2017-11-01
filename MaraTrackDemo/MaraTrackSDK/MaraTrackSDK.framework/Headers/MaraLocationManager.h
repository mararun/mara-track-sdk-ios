//
//  MaraLocationManager.h
//  MaraAMapLocationFramework
//
//  Created by pk on 2017/7/28.
//  Copyright © 2017年 com.maramara. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreLocation/CoreLocation.h>

/**
 定位返回Block

 @param location 定位信息
 @param error 错误信息，参考 CLError
 */
typedef void (^UpdateLocationCompletionBlock)(CLLocation *location, NSError *error);

@interface MaraLocationManager : NSObject

///**
// 初始化并返回值
//
// @param completionBlock 数据回调block
// @return MaraLocationManager实例
// */
//- (id)initWithCompletionBlock:(UpdateLocationCompletionBlock)completionBlock;

/**
 *  @brief 开始连续定位。
 */
- (void)startUpdatingLocation;

/**
 *  @brief 停止连续定位。
 */
- (void)stopUpdatingLocation;


@property (nonatomic, copy) UpdateLocationCompletionBlock updateLocationCompletionHandler;

@end
