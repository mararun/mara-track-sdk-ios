//
//  FileUploader.h
//  MaraTrackSDK
//
//  Created by Yalin on 2017/8/31.
//  Copyright © 2017年 com.maramara. All rights reserved.
//

#import <Foundation/Foundation.h>

@protocol FileUploaderDelegate <NSObject>
-(void) uploadDidSucceeded: (NSString*)filePath data: (NSData*)data needDeleting: (BOOL)needDeleting;
-(void) uploadDidFailed: (NSString*)filePath data: (NSData*)data code: (NSInteger)statusCode;
@end

@interface FileUploader : NSObject<NSURLConnectionDataDelegate>

-(void) uploadFileWithURL:(NSString *)urlString
             headerParams:(NSDictionary*)headerParams
               bodyParams:(NSDictionary*)bodyParams
                  fileKey:(NSString *)fileKey
                 filePath:(NSString *)filePath
                extraData:(NSString *)extraData
                  boudary:(NSString *)boundary
                 delegate:(id<FileUploaderDelegate>)delegate
              needCompress:(BOOL)needCompress
             needDeleting:(BOOL)needDeleting;

@end
