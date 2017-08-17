

#import <Foundation/Foundation.h>
#import <CommonCrypto/CommonDigest.h>

@interface Utils : NSObject

+ (NSString *)formatTime:(int)seconds;

+ (NSString *)formatSpeed:(float)speed;
@end
