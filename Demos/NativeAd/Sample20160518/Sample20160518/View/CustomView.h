//
//  CustomView.h
//  Sample20160518
//
//  Created by DaidoujiChen on 2016/5/18.
//  Copyright © 2016年 DaidoujiChen. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <VMFiveAdNetwork/VMFiveAdNetwork.h>

@interface CustomView : UIView <VANativeAdViewRenderProtocol>

@property (weak, nonatomic) IBOutlet UILabel *titleLabel;
@property (weak, nonatomic) IBOutlet UIView *videoView;
@property (weak, nonatomic) IBOutlet UILabel *ctaLabel;

@property (nonatomic, copy) void (^onClose)(void);

@end
