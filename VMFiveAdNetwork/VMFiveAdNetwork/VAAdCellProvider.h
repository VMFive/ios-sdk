//
//  VAAdCellProvider.h
//  AdnSDK
//
//  Created by Blake Pai on 10/20/15.
//  Copyright © 2015 VMFive. All rights reserved.
//


@import UIKit;
#import "VANativeAd.h"
#import "VAAdView.h"

@class VANativeAdViewAttributeObject;
@protocol VAAdCellProviderDataSource;
@protocol VAAdCellProviderDelegate;

VAAD_EXPORT_PUBLIC
NSInteger const kVAAdCellProviderNumberOfAdsUnlimited;
VAAD_EXPORT_PUBLIC
NSInteger const kVAAdCellProviderNumberOfAdsNotInsert;
VAAD_EXPORT_PUBLIC
NSUInteger const kVAAdCellProviderAdOffsetInsertOnlyOne;

/**
 VAAdCellProvider provides card style AdCells for UITableView
 
 After register your tableView to provider, it will load numbers of ad and display them as UITableViewCell.
 
 Now you can choose __Automatically__ or __Manually__ insert method by implement protocol [VAAdCellProviderDataSource](../Protocols/VAAdCellProviderDataSource.html) or [VAAdCellProviderManuallyDataSource](../Protocols/VAAdCellProviderManuallyDataSource.html).
 
 -------
 
 Automatically provider will insert AdCells by the startIndex and offset. For example in Objective-C:
 
    -(NSUInteger)tableView:(nonnull UITableView *)tableView adStartRowInSection:(NSUInteger)section
    {
        return 1;
    }
     
    -(NSUInteger)tableView:(nonnull UITableView *)tableView adOffsetInSection:(NSUInteger)section
    {
        return 1;
    }
 

 The adCells' row index in the given section and table view will be : 1, 3, 5, 7.....
 
 @warning Please noted that all the given indexPath for your own UITableViewDelegate and UITableViewDataSource methods will be the indexPath __without__ AdCells. Take the sample code above for example, you will still get the indexPath of your cell with 0, 1, 2, 3, 4... instead of 0, 2, 4, 6, 8... IndexPath could be transform by __transformToWithoutAdAtIndexPath__ or __transfromToWithAdAtIndexPath__ if needed.
 
 
 */
@interface VAAdCellProvider : NSObject <UITableViewDelegate, UITableViewDataSource>

/** @name Properties */
@property (nonatomic, strong, nonnull) NSString *placement; ///< Placement name for ads
@property (nonatomic, assign, readonly) VAAdType adType; ///< Type for playable or video
@property (nonatomic, copy, nonnull) NSString *apiKey;                      ///< API Key for publisher
@property (nonatomic, strong, nullable) VANativeAdViewAttributeObject *attributes; ///< NativeAd attributes setting object

/**
 *Set YES to use test mode
 */
@property (nonatomic, assign) BOOL testMode;

/** @name Initial and Register Methods */


/**
 * Initial method for cell provider
 * @param placement Placement name for ads
 * @param adType Ad type for playable or video
 * @param tableView UITableView to register
 * @param attributes NativeAd attributes setting object
 * @return Instance of cell provider
 */
-(nonnull instancetype)initWithPlacement:(nonnull NSString *)placement
                                  adType:(VAAdType)adType
                               tableView:(nonnull UITableView *)tableView
                           forAttributes:(nonnull VANativeAdViewAttributeObject *)attributes;

-(nonnull instancetype)initWithNativeAds:(nonnull VANativeAds *)nativeAds
                               tableView:(nonnull UITableView *)tableView
                           forAttributes:(nonnull VANativeAdViewAttributeObject *)attributes;


/** @name Delegates and DataSources */

/**
 *  Load AdCells
 *
 *  @param isAutomatically If this argument is TRUE, [VAAdCellProviderDataSource](../Protocols/VAAdCellProviderDataSource.html) should be implement, and [VAAdCellProviderManuallyDataSource](../Protocols/VAAdCellProviderManuallyDataSource.html) for FALSE.
 */
-(void)loadAds;


/**
 *  Remove AdCells
 */
-(void)unloadAds;

-(void)beginUpdates;
-(void)endUpdates;


/** @name Index Convertation Methods */

/**
 *  Get IndexPath with adCells
 *
 *  @param indexPath IndexPath without adCells
 *
 *  @return IndexPath with adCells
 */
-(nonnull NSIndexPath *)transformToWithAdAtIndexPath:(nonnull NSIndexPath *)indexPath;

/**
 *  Get IndexPath without adCells
 *
 *  @param indexPath IndexPath with adCells
 *
 *  @return IndexPath without adCells
 */
-(nonnull NSIndexPath *)transformToWithoutAdAtIndexPath:(nonnull NSIndexPath *)indexPath;

@end

/** 
 * VAAdCellProvider Delegate
 */

@protocol VAAdCellProviderDelegate <NSObject>
@optional

/**
 *  AdCell did load at IndexPath
 *
 *  @param adCellProvider AdCellProvider of this AdCell
 *  @param indexPath      IndexPath of this AdCell
 */
- (void)adCellProvider:(nonnull VAAdCellProvider *)adCellProvider didLoadAtIndexPath:(nonnull NSIndexPath *)indexPath;

/**
 *  AdCellProvider loadAd was failed. (All the AdCells will be removed after this delegate)
 *
 *  @param adCellProvider VAAdCellProvider which failed to load
 *  @param error          NSError with error code and message
 */
- (void)adCellProvider:(nonnull VAAdCellProvider *)adCellProvider didFailWithError:(nonnull NSError *)error;

/**
 *  AdCell did fail to load at IndexPath
 *
 *  @param adCellProvider AdCellProvider of this AdCell
 *  @param indexPath      IndexPath of this AdCell (the row of this indexPath will be remove after
 * this delegate called)
 *  @param error          NSError with error code and message
 */
- (void)adCellProvider:(nonnull VAAdCellProvider *)adCellProvider
	didFailAtIndexPath:(nonnull NSIndexPath *)indexPath
			 withError:(nonnull NSError *)error;

/**
 *  One of AdCell was click
 *
 *  @param adCellProvider AdCellProvider of clicked AdCell
 */
- (void)adCellProviderDidClick:(nonnull VAAdCellProvider *)adCellProvider;

/**
 *  One of AdCell finished handling click
 *
 *  @param adCellProvider AdCellProvider of finished handling click AdCell
 */
- (void)adCellProviderDidFinishHandlingClick:(nonnull VAAdCellProvider *)adCellProvider;


// Deprecated delegates

/**
 *  AdCell did load
 *
 *  @param indexPath IndexPath of the AdCell was loaded
 */
- (void)adCellDidLoadAtIndexPath:(nonnull NSIndexPath *)indexPath __deprecated;


/**
 *  AdCell load fail
 *
 *  @param indexPath IndexPath of the AdCell was failed
 *  @param error     NSError object
 */
- (void)adCellAtIndexPath:(nonnull NSIndexPath *)indexPath didFailWithError:(nonnull NSError *)error __deprecated;


@end

/** 
 * VAAdCellProvider Automatically Data Source
 */
@protocol VAAdCellProviderDataSource <NSObject>
@required
/**
 *  Delegate to get first ad index in this section
 *
 *  @param tableView UITableView to detect
 *  @param section   Section to detect
 *
 *  @return Index of first Ad
 */
-(NSUInteger)tableView:(nonnull UITableView *)tableView adStartRowInSection:(NSUInteger)section;

@optional

/**
 *  Delegate to get the offset between ads  
 *  @warning if delegate @selector(tableView:numberOfAdsInSection:) was not implemented, and then then minimum value here will be 1 (which means if this delegate returned 0, it will be transform to 1 automatically
 *
 *  @param tableView UITableView to detect
 *  @param section   Section to detect
 *
 *  @return Offset between two Ads
 */
-(NSUInteger)tableView:(nonnull UITableView *)tableView adOffsetInSection:(NSUInteger)section;


/**
 *  Number of Ad in the giving secion of tableView
 *
 *  @param tableView UITableView to detect
 *  @param section   Section to detect
 *
 *  @return Number of Ads for this section in tableView
 */
-(NSInteger)tableView:(nonnull UITableView *)tableView numberOfAdsInSection:(NSUInteger)section;

@end
