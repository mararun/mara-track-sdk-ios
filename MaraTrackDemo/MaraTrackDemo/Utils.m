//
//  Utils.m
//  funMatch_iPad
//
//  Created by Dean on 12-5-14.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "Utils.h"
#import <sys/utsname.h>
@implementation Utils

+ (NSString *)formatTime:(int)seconds {
    if(!seconds || seconds == 0)return @"00:00:00";
    /**
     *  以小时显示的
     */
    int hour = seconds / 3600;
    NSMutableString * str = [[NSMutableString alloc] init];
    if (hour < 10) {
        [str setString:@"0"];
    }
    hour = floor(hour);

    [str appendFormat:@"%d",hour];
    [str appendString:@":"];
    int  minute = (seconds -hour*3600)/60;
    //    int  minute = seconds/60; 以分钟显示的
    if (minute < 10) {
        [str appendString:@"0"];
    }
    minute = floor(minute);

    [str appendFormat:@"%d",minute];
    /**
     *  这边注释掉的时间是以秒来向上增加的
     */
    [str appendString:@":"];
    int second = (seconds -hour*3600) % 60;
    if (second < 10) {
        [str appendString:@"0"];
    }
    second = round(second);
    [str appendFormat:@"%d",second];

    return str;
}

+ (NSString *)formatSpeed:(float)speed {
    speed = speed / 60.0;
    if (speed <= 0.001) {
        return @"00'00''";
    }
    NSString *timeString = [NSString stringWithFormat:@"%.2f",speed];
    NSArray *timeArray = [timeString componentsSeparatedByString:@"."];
    int miniStr = [[timeArray firstObject] intValue];
    float secint = [[timeArray lastObject] floatValue];

    int secStr = secint/100*60;

    NSString *speedStr = [NSString stringWithFormat:@"%d'%d''",miniStr,secStr];
    if (secStr < 10 && miniStr <10) {
        speedStr = [NSString stringWithFormat:@"0%d'0%d''",miniStr,secStr];
    }else if(secStr <10){
        speedStr = [NSString stringWithFormat:@"%d'0%d''",miniStr,secStr];
    }else if (miniStr <10){
        speedStr = [NSString stringWithFormat:@"0%d'%d''",miniStr,secStr];
    }
    return speedStr;
}
@end
