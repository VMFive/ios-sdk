//
//  VANativeAdViewRenderProtocol.h
//  AdnSDK
//
//  Created by Blake Pai on 12/9/15.
//  Copyright © 2015 VMFive. All rights reserved.
//

#import <Foundation/Foundation.h>

/**
 *  VANativeAdViewRenderProtocol
 */

@protocol VANativeAdViewRenderProtocol <NSObject>

/**
 *  Please refer to VMFiveAdNetworkSampleApp -> VideoNativeRenderViewController
 */

@optional

-(nonnull UILabel *)nativeTitleTextLabel;
-(nonnull UILabel *)nativeDescriptionTextLabel;
-(nonnull UILabel *)nativeSubtitleTextLabel;
-(nonnull UILabel *)nativeCallToActionTextLabel;
-(nonnull UITextField *)descriptionTextField;

-(nonnull UIView *)nativeVideoView;
-(nonnull UIImageView *)coverImageView NS_UNAVAILABLE; /// < 目前直接加入在videoView中

-(nonnull UIImageView *)nativeMainImageView;
-(nonnull UIImageView *)nativeIconImageView;

/**
 *  Implement this protocol if you don't want entire AdView is clickable
 *
 *  For example, you want an UILabel and UIButton to be become CTA (CallToAction) trigger, you can implement this protocol like below
 *
 *      -(NSArray *)clickableViews
 *      {
 *          return @[aLabel, aButton];
 *      }
 *
 *  @return Clickable views to register CallToAction monitor
 */
-(nonnull NSArray *)clickableViews;


/**
 *  This protocol should return an UINib contain only one UIView that is conform to VANatvieAdViewRenderProtocol
 *
 *  @return An UINib contains an Custom AdView
 */
+(nonnull UINib *)nibForAd;

@end
