//
//  VAAdRewardedVideo.h
//  AdnSDK
//
//  Created by DaidoujiChen on 2016/5/12.
//  Copyright © 2016年 VMFive. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "VAAdView.h"

@protocol VAAdRewardedVideoDelegate;

@interface VAAdRewardedVideo : UIViewController <UIPopoverControllerDelegate>

@property (nonnull, nonatomic, readonly) NSString *placement;
@property (nonnull, nonatomic, copy) NSString *apiKey;
@property (nullable, nonatomic, weak) id<VAAdRewardedVideoDelegate> delegate;
@property (nonatomic, assign) VAAdType adType;
@property (nonatomic, assign) BOOL testMode;

-(nonnull instancetype)initWithplacement:(nonnull NSString *)placement;
-(nonnull instancetype)initWithNativeAds:(nonnull VANativeAds *)nativeAds;
-(void)loadAd;
-(void)show;

@end

@interface VAAdRewarded : NSObject

@property (nonnull, nonatomic, copy) NSString *currencyType;
@property (nonnull, nonatomic) NSNumber *amount;

@end

@protocol VAAdRewardedVideoDelegate <NSObject>

@optional
-(void)rewardedVideoDidLoad:(nonnull VAAdRewardedVideo *)rewardedVideo;
-(void)rewardedVideoWillShow:(nonnull VAAdRewardedVideo *)rewardedVideo;
-(void)rewardedVideoDidShow:(nonnull VAAdRewardedVideo *)rewardedVideo;

-(void)rewardedVideoWillClose:(nonnull VAAdRewardedVideo *)rewardedVideo;
-(void)rewardedVideoDidClose:(nonnull VAAdRewardedVideo *)rewardedVideo;

-(void)rewardedVideoDidClick:(nonnull VAAdRewardedVideo *)rewardedVideo;
-(void)rewardedVideoDidFinishHandlingClick:(nonnull VAAdRewardedVideo *)rewardedVideo;
-(nonnull NSString *)rewardedCustomString;
-(void)rewardedVideo:(nonnull VAAdRewardedVideo *)rewardedVideo shouldReward:(nonnull VAAdRewarded *)rewarded;

-(void)rewardedVideo:(nonnull VAAdRewardedVideo *)rewardedVideo didFailWithError:(nonnull NSError *)error;

@end
