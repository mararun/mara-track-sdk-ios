//
//  MaraTrackerRecordUploadManager.h
//  MaraTrackSDK
//
//  Created by Yalin on 2017/8/29.
//  Copyright © 2017年 com.maramara. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "FileUploader.h"

@protocol MaraTrackerRecordUploadManagerDelegate <NSObject>
- (void)recordUploadResult: (BOOL)success data: (NSData*)data filePath: (NSString*)filePath code: (NSInteger)statusCode;
@end

@interface MaraTrackerRecordUploadManager : NSObject <FileUploaderDelegate>

+(instancetype)shareInstance;

/**
 上传所有本地跑步记录
 */
- (void)uploadAllRecords: (id<MaraTrackerRecordUploadManagerDelegate>)delegate;

/**
 上传单条跑步记录

 @return NO：参数不正确 or 正在上传中
 */
- (RecordUploadResult)uploadOneRecord: (NSString*)path
                            extraData: (NSString*)extraData
               delegate: (id<MaraTrackerRecordUploadManagerDelegate>)delegate
             biz_userID: (NSString*) bizUserID;
@end
