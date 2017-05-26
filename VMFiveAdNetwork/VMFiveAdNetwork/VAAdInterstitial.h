//
//  VAAdInterstitial.h
//  AdnSDK
//
//  Created by Blake Pai on 8/25/15.
//  Copyright (c) 2015 VMFive. All rights reserved.
//

@import UIKit;
#import "VAAdView.h"


@protocol VAAdInterstitialDelegate;

/**
 VAAdInterstitial is an UIViewController containing an VAAdView that provide Interstitial style ad
 
 Objective-C example :
 
    VAAdInterstitialAd *interstitialAd = [[VAAdInterstitialAd alloc] initWithPlacement:@"interstitial.default"];

    [interstitialAd setDelegate:self];
    [interstitialAd loadAd];
 
    // ...
    // some codes
    // ...
 
    if (interstitialAd.adValid)
    {
        // This example will generate a fullscreen interstitial
        UIViewController *rootViewController = [UIApplication sharedApplication].keyWindow.rootViewController;
        [interstitialAd showAdFromViewController:rootViewController];
    }
 
 Swift example :
 
    var interstitialAd = VAAdInterstitial(withplacement: "interstitial.default")
 
    interstitialAd.delegate = self;
    interstitialAd.loadAd()
 
    // ...
    // some codes
    // ...
 
    if interstitialAd.adValid
    {
        if let rootViewController = UIApplication.sharedApplication().keyWindow?.rootViewController?
        {
            interstitialAd.showAdFromViewController(rootViewController)
        }
 
    }
 
 Instead of monitoring adValid's value, you can determine if an interstitial was ready to show by implement [VAAdInterstitialDelegate](../Protocols/VAAdInterstitialDelegate.html).
 
 
 */
@interface VAAdInterstitial : UIViewController <UIPopoverControllerDelegate, VAAdViewDelegate>

/** @name Properties */
@property (nonatomic, copy, readonly, nonnull) NSString *placement; ///< Placement string tag
@property (nonatomic, assign) VAAdType adType;
@property (nonatomic, copy, nonnull) NSString *apiKey;                      ///< API Key for publisher
@property (nonatomic, strong, nullable) NSArray<NSString *> *keywords;
@property (nonatomic, weak, nullable) id<VAAdInterstitialDelegate> delegate; ///< VAAdInterstitial callback delegate

/**
 *Set YES to use test mode
 */
@property (nonatomic, assign) BOOL testMode;


/** @name Methods*/

/**
 *  Initial method
 *
 *  @param placement Placement string tag
 *
 *  @param adType Ad type to request
 *
 *  @return Instance of VAAdInterstitial
 */
-(nonnull instancetype)initWithplacement:(nonnull NSString *)placement adType:(VAAdType)adType;

-(nonnull instancetype)initWithNativeAds:(nonnull VANativeAds *)nativeAds;

/**
 *  Load Ad
 */
-(void) loadAd;

/**
 *  Present Interstitial adView from specific viewController
 *
 *  @param viewController ViewController to present Interstitial adView. Nullable.
 */
-(void) showAdFromViewController:(nullable UIViewController *)viewController;

@end

/** @name Delegate */

/**
 *  VAAdInterstitial callback delegate
 */
@protocol VAAdInterstitialDelegate <NSObject>

@optional

/**
 *  CTA on interstitial ad was clicked
 *
 *  @param interstitialAd VAAdInterstitial that was clicked
 */
- (void)interstitialAdDidClick:(nonnull VAAdInterstitial *)interstitialAd;

/**
 *  Will be called before VAAdInterstitial view closed
 *
 *  @param interstitialAd Interstitial AdView that is going to be closed
 */
- (void)interstitialAdWillClose:(nonnull VAAdInterstitial *)interstitialAd;

/**
 *  Will be called after VAAdInterstitial view closed
 *
 *  @param interstitialAd Insterstitial AdView was just closed
 */
- (void)interstitialAdDidClose:(nonnull VAAdInterstitial *)interstitialAd;

/**
 *  Will be called when VAAdInterstitial was loaded and ready to show
 *
 *  @param interstitialAd VAAdInterstitial was loaded
 */
- (void)interstitialAdDidLoad:(nonnull VAAdInterstitial *)interstitialAd;

/**
 *  Will be called if VAAdInterstitial failed to load
 *
 *  @param interstitialAd VAAdInterstitial failed to load
 *  @param error          NSError with error code and message
 */
- (void)interstitialAd:(nonnull VAAdInterstitial *)interstitialAd didFailWithError:(nonnull NSError *)error;

@end
