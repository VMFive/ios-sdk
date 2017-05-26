//
//  VANativeAds.h
//  AdnSDK
//
//  Created by DaidoujiChen on 2017/3/13.
//  Copyright © 2017年 VMFive. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "VANativeAd.h"
#import "VANativeAdProperty.h"

@interface VANativeAds : NSObject <VANativeAdDelegate>

@property (nonatomic, nullable, weak) id <VANativeAdDelegate> delegate;

@property (nonatomic, nullable, readonly) VANativeAd *nativeAd;
@property (nonatomic, readonly) VAAdType adType;
@property (nonatomic, nullable, readonly) NSArray<NSString *> *keywords;
@property (nonatomic, readonly) BOOL testMode;

+(nonnull instancetype)use:(nonnull NSArray<VANativeAdProperty *> *)adProperties withAdType:(VAAdType)adType isTestMode:(BOOL)testMode;
+(nonnull instancetype)use:(nonnull NSArray<VANativeAdProperty *> *)adProperties withAdType:(VAAdType)adType keywoards:(nullable NSArray<NSString *> *)keywords isTestMode:(BOOL)testMode;

-(void)loadAd;
-(void)loadAdWithSettings:(nonnull void (^)(VANativeAd* _Nonnull nativeAd))settings;
-(void)unloadAd;

@end
