//
//  VMFiveAd.h
//  AdnSDK
//
//  Created by Micky on 15/7/27.
//  Copyright (c) 2015年 VMFive. All rights reserved.
//

@import UIKit;
@import Foundation;

#ifdef __cplusplus
# define VAAD_EXPORT_PUBLIC  extern "C" __attribute__((visibility("default")))
#else
# define VAAD_EXPORT_PUBLIC  extern __attribute__((visibility("default")))
#endif

/**
 * NativeAd Error Code
 */
typedef NS_ENUM (NSUInteger, VAErrorCode) {
    
    VAErrorUnknown        = 0,      ///< Unknown error
    VAErrorBadRequest     = 1,      ///< Bad Requst (ex: invalid nativeAd setting)
    VAErrorNotRegistered,           ///< AdView not register
    VAErrorNotLoaded,               ///< NativeAd not loaded
    VAErrorBadNetwork,              ///< Bad Network issue
    VAErrorDownloadFailed,          ///< Download Failed issue
    VAErrorResourceCheckingFailed,  ///< Resource Checking Fail issue
    VAErrorBadView,                 ///< Bad View for registering
    VAErrorRegistered,              ///< View input has been register
    VAErrorWrongSize,               ///< View input has wrong size
    VAErrorOSNotSupport             ///< OS Version not support (should be iOS 8.0+)
};

/** Ad View Type */
typedef NS_ENUM(NSUInteger, VAAdViewType)
{
    kVAAdViewUnknow = 0,    ///< Default Zero
    kVAAdViewBanner = 1,    ///< Banner (32:5)
    kVAAdViewInterstitial,  ///< Interstitial (fullscreen)
    kVAAdViewCard,          ///< Card (customized size)
    kVAAdViewNative         ///< Native (no size)
};

/** Ad Campaign Type */
typedef NS_OPTIONS(NSUInteger, VAAdCampType) {
    kVAAdCampUnknow = 0, ///< Default Zero
    kVAAdCampVideo = 1 ,      ///< Video type
};

/**
 
 Structure defines ad view resource type and size
 
 Throught VAAdType, you can request difference resource type for any purpose. We provided 7 preset VAAdTypes for general usage.
 
    {
        kVAAdTypeZero,              ///< Default invalid VAAdType
        kVAAdTypeBanner,            ///< VAAdType for image banner
        kVAAdTypeVideoBanner,       ///< VAAdType for video bannder
        kVAAdTypeInterstitial,      ///< VAAdType for interstitial ad
        kVAAdTypeVideoInterstitial  ///< VAAdType for video interstitial ad
        kVAAdTypeCard,              ///< VAAdType for card ad
        kVAAdTypeVideoCard,         ///< VAAdType for video card ad
        kVAAdTypeNative             ///< VAAdType for native ad
    }
 
Also, you can define a customized adType. Please check the example below :
 
    // 640x480 video interstitial type resource
    VAAdType customizedAdType = {kVAAdViewInterstitial, kVAAdCampVideo, {640, 480}};

 */
typedef struct VAAdType
{
    /**
     *  [AdView Type](../Constants/VAAdViewType.html) for view type
     */
    VAAdViewType adViewType;
    
    /**
     *  [AdCampaign Type](../Constants/VAAdCampType.html) for campaign type
     */
    VAAdCampType adCampType;
    
    /**
     *  CGSize for view size
     */
    CGSize size;

}VAAdType;


VAAD_EXPORT_PUBLIC
VAAdType const kVAAdTypeZero;               ///< Default invalid VAAdType
VAAD_EXPORT_PUBLIC
VAAdType const kVAAdTypeBanner;             ///< VAAdType for image banner
VAAD_EXPORT_PUBLIC
VAAdType const kVAAdTypeVideoBanner;        ///< VAAdType for video bannder
VAAD_EXPORT_PUBLIC
VAAdType const kVAAdTypeInterstitial;       ///< VAAdType for interstitial ad
VAAD_EXPORT_PUBLIC
VAAdType const kVAAdTypeVideoInterstitial;  ///< VAAdType for video interstitial ad
VAAD_EXPORT_PUBLIC
VAAdType const kVAAdTypeCard;               ///< VAAdType for card ad
VAAD_EXPORT_PUBLIC
VAAdType const kVAAdTypeVideoCard;          ///< VAAdType for video card ad

/**
 *  Video Player Mode
 */
typedef NS_ENUM(NSUInteger, VAAdPlayerDisplayMode) {
    /**
     *  One time play with replay button at the end of video
     */
    kVAAdPlayerDisplayModeOneTimePreview,
    /**
     *  Auto repeat
     */
    kVAAdPlayerDisplayModeRepeatPreview,
};

@class VAAdMediaViewConfig;
@protocol VANativeAdDelegate;

/**
 VANativeAd is configurable object for VMFive AD Network. It will loads everything you need for customized ad view by your own style through asynchonized http request. If any task was finished or failed, and then delegates defined in [VANativeAdDelegate](../Protocols/VANativeAdDelegate.html) will be called.

 Objective-C example :
 
    VANativeAd *nativeAd = [[VANativeAd alloc] initWithPlacement:@"placement.default" adType:kVAAdTypeVideoBanner];
    nativeAd.apiKey = YOUR_KEY;
    [nativeAd loadAd];
 
 Swift example :
 
    var nativeAd = VANativeAd(withplacement: "placement.default", adType: kVAAdTypeVideoBanner)
    nativeAd.apiKey = YOUR_KEY
    nativeAd.loadAd()

 About __adType__ setting, please check reference for [VAAdType](../DataTypes/VAAdType.html).
 
 */

@interface VANativeAd : NSObject

/** @name Properties */

@property (nonatomic, strong, readonly, nonnull) NSUUID *uuid;              ///< Unique ID
@property (nonatomic, copy, readonly, nonnull) NSString *placement;                   ///< Placement tag string


/**
 Ad preset type
 
 All the NativeAds with the same placement and adType will be the same style. see [VAAdType]
 */
@property (nonatomic, assign, readonly) VAAdType adType;

@property (nonatomic, copy, nonnull) NSString *apiKey;                      ///< API Key for publisher

@property (nonatomic, weak, nullable) id <VANativeAdDelegate> delegate;     ///< NativeAd callback delegate. See [VANativeDelegate](../Protocols/VANativeAdDelegate.html)

@property (nonatomic, assign) BOOL testMode;                                ///< Set YES to use test mode

@property (nonatomic, assign, readonly) BOOL isValid;                       ///< Will be true if NativeAd was loaded


/** @name Ad Information & Resource Properties */

@property (nonatomic, copy, readonly, nullable) NSString *titleText;                        ///< Ad Title Text
@property (nonatomic, copy, readonly, nullable) NSString *descriptionText;                  ///< Ad Description Text
@property (nonatomic, copy, readonly, nullable) NSString *subtitleText;                     ///< Ad Subtitle Text
@property (nonatomic, copy, readonly, nullable) NSString *ctaText;                          ///< Ad CTA Text

@property (nonatomic, readonly, nullable) NSString *imageURL;
@property (nonatomic, readonly, nullable) UIImage *image;                                   ///< Ad Main Image
@property (nonatomic, readonly) CGSize imageSize;                                           ///< Ad Main Image Size

@property (nonatomic, readonly, nullable) NSString *iconURL;
@property (nonatomic, readonly, nullable) UIImage *iconImage;                               ///< Ad Icon
@property (nonatomic, readonly) CGSize iconSize;                                            ///< Ad Icon Size

@property (nonatomic, readonly, nullable) NSString *coverImageURL;
@property (nonatomic, readonly, nullable) UIImage *coverImage;                              ///< Ad Main Image
@property (nonatomic, readonly) CGSize coverImageSize;                                      ///< Ad Main Image Size

@property (nonatomic, readonly, nullable) NSString *vastString;                             ///< VAST 2.0 XML String
@property (nonatomic, readonly, nullable) UIView *mediaView;                                ///< Media view with default action defined by adType
@property (nonatomic, readonly) CGSize mediaSize;                                           ///< Media View Size


@property (nonatomic, readonly, nullable) NSString *destinationURL;                         /// CTA URL


/** @name Methods */

/**
 *  Get version of AdNetwork SDK version
 *
 *  @return Version string of AdNetwork SDK
 */
+ (nonnull NSString *)version;

/**
 *  Enable/Disable local log
 *
 *  @param enable YES(true) for enable and NO(false) for disable
 *  @param isDetail If isDetail was NO(false), only Errors will be printed
 */
+ (void)enableLocalLog:(BOOL)enable isDetail:(BOOL)isDetail;

/**
 *  Initialize NativeAd by placement string and ad type
 *
 *  @param placement Placement for the same placement tag
 *  @param adType    Ad type to request
 *
 *  @return Instance of nativeAd
 */
- (nonnull instancetype)initWithPlacement:(nonnull NSString *)placement
                                   adType:(VAAdType)adType;

/**
 *  Load ad information and resource. VANativeAdDelegate will be called once it finished
 */
- (void)loadAd;

/**
 *  Unload Ad Object (release Resources and AdInfo)
 */
- (void)unloadAd;


/**
 *  Register a view for impression and action
 *
 *  @param view           Ad view to register
 *  @param viewController View controller to present adView (ex: your RootViewController)
 *
 *  @return 註冊結果（結果為NO則表示此AdView無法正常運作）
 */
- (BOOL)registerForInteraction:(nonnull UIView *)view
            withViewController:(nullable UIViewController *)viewController;

/**
 *  Register a view and clickable views for impression and action
 *
 *  @param view           Ad View to register
 *  @param viewController View Controller to present adView (ex: rootViewController)
 *  @param clickableViews Subviews that can be clicked on adView for perform action
 *
 *  @return 註冊結果（結果為NO則表示此AdView無法正常運作）
 */
- (BOOL)registerForInteraction:(nonnull UIView *)view
            withViewController:(nullable UIViewController *)viewController
            withClickableViews:(nullable NSArray *)clickableViews;

/**
 *  Unregister ad view if you don't need it anymore or you are going to reload this NativeAd
 *
 *  @return 反註冊結果
 */
- (BOOL)unregisterView;

/**
 *  Action is default triggered by clicks. Call performAction if you want to make it to be programmatically
 */
- (void)performAction;

@end

/**
 * NativeAd callback delegate
 */
@protocol VANativeAdDelegate <NSObject>

@optional

/**
 * NativeAd load success
 * @brief Will be called once NativeAd loaded success
 * @param nativeAd NativeAd that was loaded success
 */
- (void)nativeAdDidLoad:(nonnull VANativeAd *)nativeAd;

/**
 * NativeAd load failed
 * @brief Will be called once NativeAd loaded success
 * @param nativeAd NativeAd that was loaded failed
 * @param error NSError contains error code and error message
 */
- (void)nativeAd:(nonnull VANativeAd *)nativeAd didFailedWithError:(nonnull NSError *)error;

/**
 * Ad view registered in NativeAd was clicked
 * @brief Will be called if CTA was triggered by click
 * @param nativeAd NativeAd that perform the action
 */
- (void)nativeAdDidClick:(nonnull VANativeAd *)nativeAd;

/**
 * Action by clicked has finished
 * @brief Will be called if CTA has finished
 * @param nativeAd NativeAd that perform the action
 */
- (void)nativeAdDidFinishHandlingClick:(nonnull VANativeAd *)nativeAd;


-(void)nativeAdBeImpressed:(nonnull VANativeAd *)nativeAd;

/**
 *  NativeAd could be reload
 *
 *  @param nativeAd NativeAd which did finish impression
 */
- (void)nativeAdDidFinishImpression:(nonnull VANativeAd *)nativeAd;

@end

