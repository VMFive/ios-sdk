//
//  VANativeAdProperty.h
//  AdnSDK
//
//  Created by DaidoujiChen on 2017/3/13.
//  Copyright © 2017年 VMFive. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface VANativeAdProperty : NSObject

@property (nonatomic, nonnull, strong) NSString *apiKey;
@property (nonatomic, nonnull, strong) NSString *placement;
@property (nonatomic, assign) NSInteger priority;
@property (nonatomic, nullable, strong) NSString *identifier;

+(nonnull VANativeAdProperty *)key:(nonnull NSString *)apiKey placement:(nonnull NSString *)placement priority:(NSInteger)priority identifier:(nullable NSString *)identifier;
+(nonnull VANativeAdProperty *)key:(nonnull NSString *)apiKey placement:(nonnull NSString *)placement priority:(NSInteger)priority;

@end
