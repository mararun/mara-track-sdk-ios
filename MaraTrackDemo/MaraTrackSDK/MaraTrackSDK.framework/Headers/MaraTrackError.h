//
//  MaraTrackError.h
//  MaraTrackSDK
//
//  Created by Yalin on 2017/11/6.
//  Copyright © 2017年 com.maramara. All rights reserved.
//

#ifndef MaraTrackError_h
#define MaraTrackError_h

typedef NS_ENUM(int32_t, MaraTrackError) {
    MaraTrackErrorNoError           = 0,
    
    MaraTrackErrorStopRunning       = 1,
    MaraTrackErrorGetTrackInfo      = 2,
    MaraTrackErrorSaveTrack         = 3,
    MaraTrackErrorPedometer         = 4,
};

#endif /* MaraTrackError_h */
