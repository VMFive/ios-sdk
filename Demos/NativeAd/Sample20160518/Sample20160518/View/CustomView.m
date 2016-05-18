//
//  CustomView.m
//  Sample20160518
//
//  Created by DaidoujiChen on 2016/5/18.
//  Copyright © 2016年 DaidoujiChen. All rights reserved.
//

#import "CustomView.h"

@implementation CustomView

#pragma mark - VANativeAdViewRenderProtocol

+ (UINib *)nibForAd {
    return [UINib nibWithNibName:@"CustomView" bundle:nil];
}

- (UILabel *)nativeTitleTextLabel {
    return self.titleLabel;
}

- (UIView *)nativeVideoView {
    return self.videoView;
}

- (NSArray *)clickableViews {
    return @[ self.ctaLabel ];
}

#pragma mark - IBAction

- (IBAction)closeAction:(id)sender {
    if (self.onClose) {
        self.onClose();
    }
}

@end
