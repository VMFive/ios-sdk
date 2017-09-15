//
//  VAAdSplash.h
//  AdnSDK
//
//  Created by DaidoujiChen on 2017/8/11.
//  Copyright © 2017年 VMFive. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "VAAdView.h"

@protocol VAAdSplashDelegate;

@interface VAAdSplash : UIViewController

@property (nonatomic, copy, readonly, nonnull) NSString *placement;
@property (nonatomic, copy, nonnull) NSString *apiKey;
@property (nonatomic, strong, nullable) NSArray<NSString *> *keywords;
@property (nonatomic, weak, nullable) id<VAAdSplashDelegate> delegate;
@property (nonatomic, assign) VAAdType adType;
@property (nonatomic, assign) BOOL testMode;

-(nonnull instancetype)initWithplacement:(nonnull NSString *)placement adType:(VAAdType)adType;
-(nonnull instancetype)initWithNativeAds:(nonnull VANativeAds *)nativeAds;
-(void)loadAd;
-(void)showAdFromViewController:(nullable UIViewController *)viewController;

@end

@protocol VAAdSplashDelegate <NSObject>

@optional
-(void)splashAdDidClick:(nonnull VAAdSplash *)splashAd;
-(void)splashAdWillClose:(nonnull VAAdSplash *)splashAd;
-(void)splashAdDidClose:(nonnull VAAdSplash *)splashAd;
-(void)splashAdDidLoad:(nonnull VAAdSplash *)splashAd;
-(void)splashAd:(nonnull VAAdSplash *)splashAd didFailWithError:(nonnull NSError *)error;

@end
