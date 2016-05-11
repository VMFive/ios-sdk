//
//  VANativeAdViewRender.h
//  AdnSDK
//
//  Created by Blake Pai on 12/3/15.
//  Copyright © 2015 VMFive. All rights reserved.
//

@import UIKit;

@class VANativeAd;
@protocol VANativeAdViewRenderProtocol;
@protocol VANativeAdViewRenderDelegate;

/**
 
 VANAtiveAdViewRender can render resources of a NativeAd object to a custom AdView
 
 */

@interface VANativeAdViewRender : NSObject

/** @name Properties */

@property (nullable, nonatomic, weak) id<VANativeAdViewRenderDelegate> delegate; ///< Delegate for VANativeAdViewRender

/** @name Initial and Register Methods */

/**
 *  Initial an render by pass NativeAd and AdView object
 *
 *  @param nativeAd NativeAd object has been loaded
 *  @param adView   AdView to render
 *
 *  @return Instance of VANativeAdViewRender
 */
-(nonnull instancetype)initWithNativeAd:(nonnull VANativeAd *)nativeAd
                   customAdView:(nonnull UIView<VANativeAdViewRenderProtocol> *)adView;

/**
 *  Initial an render by pass NativeAd object and AdView class
 *
 *  @param nativeAd    NativeAd object has been loaded
 *  @param adViewClass AdView class to allocate and render
 *
 *  @return Instance of VANAtiveAdViewRender
 */
-(nonnull instancetype)initWithNativeAd:(nonnull VANativeAd *)nativeAd
          customizedAdViewClass:(nonnull Class)adViewClass;


/**
 *  Async Render
 *
 *  @param completeHandler complete handler to handle adView
 */
- (void)renderWithCompleteHandler:(void (^_Nullable)(UIView<VANativeAdViewRenderProtocol> *_Nullable, NSError *_Nullable))completeHandler;

@end


/**
 *  Delegate for VANativeAdViewRender
 */
@protocol VANativeAdViewRenderDelegate <NSObject>

@optional

/**
 *  Get UIViewController for Modal Views
 *
 *  @return UIViewController to present Modal View (If is nil, [[[UIApplication sharedApplication] keyWindow] rootViewController] will be used)
 */
-(nullable UIViewController *)viewControllerForPresentModalView;


@end



