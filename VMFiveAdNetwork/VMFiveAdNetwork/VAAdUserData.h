//
//  VAAdUserData.h
//  AdnSDK
//
//  Created by DaidoujiChen on 2016/12/22.
//  Copyright © 2016年 VMFive. All rights reserved.
//

#import <Foundation/Foundation.h>

typedef enum {
    VAAdUserDataGenderMale,
    VAAdUserDataGenderFemale,
    VAAdUserDataGenderOther,
} VAAdUserDataGender;

@interface VAAdUserData : NSObject

+(void)sendGender:(VAAdUserDataGender)gender;
+(void)sendAge:(NSUInteger)age;
+(void)sendKeywords:(NSArray <NSString *> *)keywords;
+(void)sendCustom:(NSDictionary *)custom;

@end
