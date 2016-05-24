//
//  VAAdView.h
//  AdnSDK
//
//  Created by Blake Pai on 8/19/15.
//  Copyright (c) 2015 VMFive. All rights reserved.
//

@import UIKit;
#import "VANativeAd.h"




@protocol VAAdViewDelegate;
@class VANativeAdViewAttributeObject;

/** Banner Auto Refresh Time */
typedef NS_ENUM(NSInteger, VAAdViewAutoRefreshTime)
{
    VAAdViewDisableRefresh  = -1, ///< Disable auto refresh. Auto refresh won't be trigger until next VAAdView instance was created
    VAAdViewRefreshShort    = 60,   ///< Auto refresh after 60 seconds
    VAAdViewRefreshMedium   = 90,   ///< Auto refresh after 90 seconds
    VAAdViewRefreshLong     = 120   ///< Auto refresh after 120 seconds
    
};

/**
 VAAdView is a preset layout ad view inherit from UIView. By correct settings and __loadAd__ method, VAAdView could be layout to be a __banner__, a __fullscreen interstitial__ or __tableView embedded card__ automatically.
 
 @warning VAAdView is __only recommended__ to be used on banner. If you want to create interstitial style or card style ads, please check [VAAdInterstitial](./VAAdInterstitial.html) or [VAAdCellProvider](./VAAdCellProvider.html).
 
 Objective-C example :
    
    UIViewController *rootViewController = [UIApplication sharedApplication].keyWindow.rootViewController;
 
    VAAdView *adView = [[VAAdView alloc] initWithplacement:@"banner.default" 
                                                    adType:kVAAdTypeVideoBanner 
                                        rootViewController:rootViewController];
 
    [adView setDelegate:self];
    [adView loadAd];
 
 Swift example :
 
    var adView:VAAdView? = nil
 
    if let rootViewController = UIApplication.sharedApplication().keyWindow?.rootViewController?
    {
        adView = VAAdView(withplacement: "banner.default", adType: kVAAdTypeVideoBanner, rootViewController: rootViewController)
        if let adView = adView
        {
            adView.delegate = self
            adView.loadAd()
        }
    }
 
 Delegates will be called after loadAd is finished, please check them in [VAAdViewDelegate](../Protocols/VAAdViewDelegate.html).
 
 */
@interface VAAdView : UIView

/** @name Properties */

/**
 * Placement string tag
 */
@property (nonatomic, copy, nonnull) NSString *placement;

/**
 * Ad preset type
 *
 * All the NativeAds with the same placement and adType will be the same style. see [VAAdType]
 */
@property (nonatomic, assign) VAAdType adType;

/**
 * API Key for publisher
 */
@property (nonatomic, copy, nonnull) NSString *apiKey;

/**
 RootViewController of view hierarchy that VAAdView will be in.
 
 If not set, this property value will be
    
 Objective-C :
 
    [UIApplication sharedApplication].keyWindow.rootViewController
 
 Swift :
 
    UIApplication.sharedApplication().keyWindow?.rootViewController?
 
 */
@property (nonatomic, weak, readonly, nullable) UIViewController *rootViewController;

/**
 * VAAdView callback delegate
 */
@property (nonatomic, weak, nullable) id<VAAdViewDelegate> delegate;

/**
 * Attributes for Card style layout
 *
 * See [VANativeAdViewAttributeObject](./VANativeAdViewAttributeObject.html)
 *
 */
@property (nonatomic, nullable, strong, setter=setAttributes:) VANativeAdViewAttributeObject *attributes;

/**
 *  You can set this property for auto refresh when you are using banner
 *
 * @warning Video Banner will auto refresh after (video duration+5) seconds
 */
@property (nonatomic, assign) VAAdViewAutoRefreshTime autoRefreshTime;


/**
 *Set YES to use test mode
 */
@property (nonatomic, assign) BOOL testMode;

@property (nonatomic, assign) BOOL isValid; ///< TRUE if VAAdView was ready to show

/** @name Methods */

/**
 * Initialized VAAdView with attributes
 * @param placement Placement string tag
 * @param adType NativeAd type
 * @param rootViewController RootViewController that ad view will be present
 * @param attributes Attributes for Card style layout customization
 * @return Instance of VAAdView
*/
-(nonnull instancetype)initWithplacement:(nonnull NSString *)placement
                                  adType:(VAAdType)adType
                      rootViewController:(nullable UIViewController *)rootViewController
                              attributes:(nullable VANativeAdViewAttributeObject *)attributes;

/**
 * Initialized VAAdView without attributes
 * @param placement Placement string tag
 * @param adType NativeAd type
 * @param rootViewController RootViewController that ad view will be present
 * @return Instance of VAAdView
 */
-(nonnull instancetype)initWithplacement:(nonnull NSString *)placement
                                    adType:(VAAdType)adType
                        rootViewController:(nullable UIViewController *)rootViewController;

/**
 * Load ad to display content of VAAdView
 */
-(void)loadAd;

/**
 * Disable ad content auto refresh
 * @brief Diable auto refresh forever for this VAAdView
 */
-(void)disableAutoRefresh NS_UNAVAILABLE;

@end

/** @name Delegate */

/**
 * VAAdView callback delegate
 */
@protocol VAAdViewDelegate <NSObject>
@optional

-(void)adViewBeImpressed:(nonnull VAAdView *)adView;

/**
 * VAAdView load success
 * @brief Will be called once VAAdView loaded success
 * @param adView VAAdView that was loaded success
 */
- (void)adViewDidLoad:(nonnull VAAdView *)adView;

/**
 * VAAdView load failed
 * @brief Will be called once VAAdView loaded failed
 * @param adView VAAdView that was loaded failed
 * @param error NSError that contains error code and error message
 */
- (void)adView:(nonnull VAAdView *)adView didFailWithError:(nonnull NSError *)error;

/**
 * VAAdView was clicked
 * @brief Will be called if CTA was triggered by click
 * @param adView VAAdView that perform the action
 */
- (void)adViewDidClick:(nonnull VAAdView *)adView;

/**
 * VAAdView's clicked action has finished
 * @brief Will be called if CTA has finished
 * @param adView VAAdView that perform the action
 */
- (void)adViewDidFinishHandlingClick:(nonnull VAAdView *)adView;

/**
 * Return a rootViewController to perform modalView
 * @return rootViewController to perform modalView
 */
- (nonnull UIViewController *)viewControllerForPresentingModalView;


/**
 *  Should AdView be reload
 *
 *  @param adView AdView to reload
 *
 *  @return Should reload
 */
- (BOOL)shouldAdViewBeReload:(nonnull VAAdView *)adView;

@end


/**
 * Attributes object for Card layout customization
 */

/**
 *  v2.0.13 : 
 *
 *  1. Remove nativeAdViewWidth & nativeAdViewHeight
 *  2. Add customAdViewSizeHandler (see the example above it)
 *
 */

@interface VANativeAdViewAttributeObject : NSObject

@property (nonatomic, assign) UIEdgeInsets viewMargin; ///< Image margin, default is UIEdgeInsetsZero

@property (nonatomic, nullable) Class customAdViewClass; ///< CustomAdView for VAAdCellProvider

@property (nonatomic, nullable) UIColor *customAdCellBackgroundColor; ///< Background color for VAAdCellProvider

@property (nonatomic, nullable) UIImage *customAdCellBackgroundImage; ///< Background image for VAAdCellProvider


/**
 *  CustomAdViewSizeHandler can help you setup AdView size for VAAdCellProvider
 *
 *  For example, you want to keep your customized AdView's aspect ratio as 16:9, you can setup it like the sample code below :
 *
 *      attributes.customAdViewSizeHandler = ^(CGFloat maxWidth){
 *          return CGSizeMake(maxWidth, maxWidth * 9.0f/16.0f);
 *      };
 */
@property (nonatomic, copy, nullable) CGSize(^customAdViewSizeHandler)(CGFloat maxWidth, CGFloat ratio);


@end