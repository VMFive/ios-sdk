//
//  MainViewController.m
//  Sample20160518
//
//  Created by DaidoujiChen on 2016/5/18.
//  Copyright © 2016年 DaidoujiChen. All rights reserved.
//

#import "MainViewController.h"
#import "CustomView.h"

@interface MainViewController ()

@property (weak, nonatomic) IBOutlet UITableView *tableView;

@property (nonatomic, strong) VANativeAd *nativeAd;
@property (nonatomic, strong) CustomView *adView;
@property (nonatomic, assign) BOOL isAdReady;

// dummy data
@property (nonatomic, strong) NSArray<NSString *> *titles;

@end

@implementation MainViewController

#pragma mark - VANativeAdDelegate

- (void)nativeAdDidLoad:(VANativeAd *)nativeAd {
    VANativeAdViewRender *render;
    if (!self.adView) {
        render = [[VANativeAdViewRender alloc] initWithNativeAd:nativeAd customizedAdViewClass:[CustomView class]];
    }
    else {
        render = [[VANativeAdViewRender alloc] initWithNativeAd:nativeAd customAdView:self.adView];
    }
    
    __weak MainViewController *weakSelf = self;
    [render renderWithCompleteHandler: ^(UIView<VANativeAdViewRenderProtocol> *view, NSError *error) {
        
        if (!error) {
            weakSelf.adView = (CustomView *)view;
            weakSelf.adView.onClose = ^{
                [weakSelf hideAd];
            };
        }
        else {
            NSLog(@"Error : %@", error);
        }
        weakSelf.isAdReady = (error == nil);
        [weakSelf.tableView reloadData];
    }];
}

- (void)nativeAd:(VANativeAd *)nativeAd didFailedWithError:(NSError *)error {
}

- (void)nativeAdDidClick:(VANativeAd *)nativeAd {
}

- (void)nativeAdDidFinishHandlingClick:(VANativeAd *)nativeAd {
}

- (void)nativeAdBeImpressed:(VANativeAd *)nativeAd {
}

- (void)nativeAdDidFinishImpression:(VANativeAd *)nativeAd {
}

#pragma mark - UITableViewDataSource

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section {
    return self.titles.count + self.isAdReady;
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {
    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:@"UITableViewCell" forIndexPath:indexPath];
    if (self.isAdReady && indexPath.row == 0) {
        cell.textLabel.text = self.adView.titleLabel.text;
    }
    else {
        cell.textLabel.text = self.titles[indexPath.row - self.isAdReady];
    }
    return cell;
}

#pragma mark - UITableViewDelegate

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath {
    if (self.isAdReady && indexPath.row == 0) {
        [self showAd];
    }
    else {
        UIAlertController *alert = [UIAlertController alertControllerWithTitle:@"點到了" message:self.titles[indexPath.row - self.isAdReady] preferredStyle:UIAlertControllerStyleAlert];
        UIAlertAction *action = [UIAlertAction actionWithTitle:@"確定" style:UIAlertActionStyleDefault handler:nil];
        [alert addAction:action];
        [self presentViewController:alert animated:YES completion:nil];
    }
}

#pragma mark - Private Instance Method

- (void)loadNativaAd {
    self.nativeAd = [[VANativeAd alloc] initWithPlacement:@"MyNativeAd" adType:kVAAdTypeVideoCard];
    self.nativeAd.testMode = YES;
    self.nativeAd.apiKey = @"YOUR API KEY HERE";
    self.nativeAd.delegate = self;
    [self.nativeAd loadAd];
}

- (void)showAd {
    [self.view addSubview:self.adView];
    
    self.adView.translatesAutoresizingMaskIntoConstraints = NO;
    [self.adView addConstraint:[NSLayoutConstraint constraintWithItem:self.adView attribute:NSLayoutAttributeWidth relatedBy:NSLayoutRelationEqual toItem:nil attribute:NSLayoutAttributeNotAnAttribute multiplier:1.0f constant:CGRectGetWidth(self.adView.bounds)]];
    [self.adView addConstraint:[NSLayoutConstraint constraintWithItem:self.adView attribute:NSLayoutAttributeHeight relatedBy:NSLayoutRelationEqual toItem:nil attribute:NSLayoutAttributeNotAnAttribute multiplier:1.0f constant:CGRectGetHeight(self.adView.bounds)]];
    [self.view addConstraint:[NSLayoutConstraint constraintWithItem:self.adView attribute:NSLayoutAttributeCenterX relatedBy:NSLayoutRelationEqual toItem:self.view attribute:NSLayoutAttributeCenterX multiplier:1.0f constant:0]];
    [self.view addConstraint:[NSLayoutConstraint constraintWithItem:self.adView attribute:NSLayoutAttributeCenterY relatedBy:NSLayoutRelationEqual toItem:self.view attribute:NSLayoutAttributeCenterY multiplier:1.0f constant:0]];
    [self.view layoutIfNeeded];
    
    __weak MainViewController *weakSelf = self;
    self.adView.transform = CGAffineTransformScale(CGAffineTransformIdentity, 0, 0);
    [UIView animateWithDuration:0.15f animations: ^{
        weakSelf.adView.transform = CGAffineTransformScale(CGAffineTransformIdentity, 1.2f, 1.2f);
    } completion: ^(BOOL finished) {
        [UIView animateWithDuration:0.15f animations: ^{
            weakSelf.adView.transform = CGAffineTransformScale(CGAffineTransformIdentity, 1.0f, 1.0f);
        } completion: ^(BOOL finished) {
        }];
    }];
}

- (void)hideAd {
    __weak MainViewController *weakSelf = self;
    [UIView animateWithDuration:0.15f animations: ^{
        weakSelf.adView.transform = CGAffineTransformScale(CGAffineTransformIdentity, 1.2f, 1.2f);
    } completion: ^(BOOL finished) {
        [UIView animateWithDuration:0.15f animations: ^{
            weakSelf.adView.transform = CGAffineTransformScale(CGAffineTransformIdentity, 0.2f, 0.2f);
        } completion: ^(BOOL finished) {
            [weakSelf.adView removeFromSuperview];
            [weakSelf.nativeAd loadAd];
        }];
    }];
}

#pragma mark - Life Cycle

- (void)viewDidLoad {
    [super viewDidLoad];
    [self.tableView registerClass:[UITableViewCell class] forCellReuseIdentifier:@"UITableViewCell"];
    
    // init values
    self.title = @"我的危險妻";
    self.isAdReady = NO;
    self.titles = @[ @"第四集", @"第三集", @"第二集", @"第一集"];
    
    [self loadNativaAd];
}

@end
