# Load and Show Native Ads
In the last chapter, we have created the layour `SampleView1`. In this chapter, we will use `NativeAdSample1ViewController` as an example to 
explain how `NativeAd` can be shown in `UIViewController`.

![](https://s3-ap-northeast-1.amazonaws.com/daidoujiminecraft/Daidouji/NativeAd1.gif)

There are four parts :
 * Use `NativeAd` to make Ad Requests
 * Use `VANativeAdDelegate` to detect loading status
 * Use `VANativeAdViewRender` to render `SampleView1`
 * Adjust `SampleView1` to specific locations
 
## Request Ad
Use `VANativeAd` object to request ad from server,  `loadAd` in`viewWillAppear:` , `unloadAd` in `viewWillDisappear:`  

Create `VANativeAd` . Two parameters are required

 * placement : A unique string from VM5 sales 
 * adType : `kVAAdTypeVideoCard`
 
After that, you can set `testMode` to `YES` to activate test mode, or `NO` to deactivate, 
**Please make sure test mode is off before you publish your app**

<details>
<summary>Objective-C</summary>
```objc
- (void)viewDidLoad {
    [super viewDidLoad];

    // 建立NativeAd物件做為Render的Ad資料來源
    self.nativeAd = [[VANativeAd alloc] initWithPlacement:@"VMFiveAdNetwork_NativeAdSample1" adType:kVAAdTypeVideoCard];
    self.nativeAd.testMode = YES;
    self.nativeAd.apiKey = @"YOUR API KEY HERE";
    self.nativeAd.delegate = self;
}

- (void)viewWillAppear:(BOOL)animated {
    [super viewWillAppear:animated];
    [self.nativeAd loadAd];
}

- (void)viewWillDisappear:(BOOL)animated {
    [super viewWillDisappear:animated];
    [self.nativeAd unloadAd];
}
```
</details>

<details>
<summary>Swift</summary>
```swift
private let nativeAd = VANativeAd(placement: "VMFiveAdNetwork_NativeAdSample1", adType:kVAAdTypeVideoCard)
    
override func viewDidLoad() {
    super.viewDidLoad()

    // Create NativeAd as source of Render
    self.nativeAd.testMode = true
    self.nativeAd.apiKey = "YOUR API KEY HERE"
    self.nativeAd.delegate = self
}
    
override func viewWillAppear(animated: Bool) {
    super.viewWillAppear(animated)
    self.nativeAd.loadAd()
}
    
override func viewWillDisappear(animated: Bool) {
    super.viewWillDisappear(animated)
    self.nativeAd.unloadAd()
}
```
</details>

## Implement VANativeAdDelegate

We assign the delagate of `NativeAd` to `self` , so we should declare the implementation.

<details>
<summary>Objective-C</summary>
```objc
@interface NativeAdSample1ViewController : UIViewController <VANativeAdDelegate>

@end
```
</details>

<details>
<summary>Swift</summary>
```swift
extension NativeAdSample1ViewController: VANativeAdDelegate {
}
```
</details>

Then Implement `VANativeAdDelegate` 

<details>
<summary>Objective-C</summary>
```objc
#pragma mark - VANativeAdDelegate

// When ad creatives is loaded
- (void)nativeAdDidLoad:(VANativeAd *)nativeAd {
    NSLog(@"%s", sel_getName(_cmd));
}

// An error happened. Check the error or contact 
// VM5 personnel
- (void)nativeAd:(VANativeAd *)nativeAd didFailedWithError:(NSError *)error {
    NSLog(@"%s %@", sel_getName(_cmd), error);
}

// When the Ad is clicked 
- (void)nativeAdDidClick:(VANativeAd *)nativeAd {
    NSLog(@"%s", sel_getName(_cmd));
}

// After the Ad is clicked and back to app from landing page
- (void)nativeAdDidFinishHandlingClick:(VANativeAd *)nativeAd {
    NSLog(@"%s", sel_getName(_cmd));
}

// Valid Impression 
-(void)nativeAdBeImpressed:(VANativeAd *)nativeAd {
    NSLog(@"%s", sel_getName(_cmd));
}

// End of video
- (void)nativeAdDidFinishImpression:(VANativeAd *)nativeAd {
    NSLog(@"%s", sel_getName(_cmd));
}
```
</details>

<details>
<summary>Swift</summary>
```swift

// When ad creatives is loaded
func nativeAdDidLoad(nativeAd: VANativeAd) {
    print("\(#function)")
}
    
// An error happened. Check the error or contact 
// VM5 personnel
func nativeAd(nativeAd: VANativeAd, didFailedWithError error: NSError) {
    print("\(#function) \(error)")
}
    
// When the Ad is clicked 
func nativeAdDidClick(nativeAd: VANativeAd) {
    print("\(#function)")
}
    
// After the Ad is clicked and back to app from landing page
func nativeAdDidFinishHandlingClick(nativeAd: VANativeAd) {
    print("\(#function)")
}
    
// Valid impression
func nativeAdBeImpressed(nativeAd: VANativeAd) {
    print("\(#function)")
}
    
// Video End
func nativeAdDidFinishImpression(nativeAd: VANativeAd) {
    print("\(#function)")
}
```
</details>

You don't have to implement all the delegate. You can just implement the delegate you think necessary.

## Use VANativeAdViewRender to SampleView1

If everything goes well, after receiving  `nativeAdDidLoad:` callback, We can start render Ad to a specific view we want. 
Create `VANativeAdViewRender`. Two parameters are required.

 * nativeAd
 * custom layout
 
Use `renderWithCompleteHandler:` and start to render, You can use `error` to detect if rendering is successful.

<details>
<summary>Objective-C</summary>
```objc
VANativeAdViewRender *render = [[VANativeAdViewRender alloc] initWithNativeAd:nativeAd customizedAdViewClass:[SampleView1 class]];
        
[render renderWithCompleteHandler: ^(UIView<VANativeAdViewRenderProtocol> *view, NSError *error) {
    if (!error) {
        NSLog(@"Render did success");
    }
    else {
        NSLog(@"Render did fail With error : %@", error);
    }
}];
```
</details>

<details>
<summary>Swift</summary>
```swift
let render = VANativeAdViewRender(nativeAd: nativeAd, customizedAdViewClass: SampleView1.self)
render.renderWithCompleteHandler({ (view, error) in
    if let safeError = error {
        print("Render did fail With error : \(safeError)")
    }
    else if let safeView = view {
        print("Render did success")
    }
})
```
</details>

## Placement

In this sample, we put the ad in the center. You can put it anywhere you like.

<details>
<summary>Objective-C</summary>
```objc
VANativeAdViewRender *render = [[VANativeAdViewRender alloc] initWithNativeAd:nativeAd customizedAdViewClass:[SampleView1 class]];
        
__weak NativeAdSample1ViewController *weakSelf = self;
[render renderWithCompleteHandler: ^(UIView<VANativeAdViewRenderProtocol> *view, NSError *error) {
            
    if (!error) {
        [weakSelf.view addSubview:view];
                
        // autolayout settings, fixed seize, vertical/horizontal center
        view.translatesAutoresizingMaskIntoConstraints = NO;
        [view addConstraint:[NSLayoutConstraint constraintWithItem:view attribute:NSLayoutAttributeWidth relatedBy:NSLayoutRelationEqual toItem:nil attribute:NSLayoutAttributeNotAnAttribute multiplier:1.0f constant:CGRectGetWidth(view.bounds)]];
        [view addConstraint:[NSLayoutConstraint constraintWithItem:view attribute:NSLayoutAttributeHeight relatedBy:NSLayoutRelationEqual toItem:nil attribute:NSLayoutAttributeNotAnAttribute multiplier:1.0f constant:CGRectGetHeight(view.bounds)]];
                
        [weakSelf.view addConstraint:[NSLayoutConstraint constraintWithItem:view attribute:NSLayoutAttributeCenterX relatedBy:NSLayoutRelationEqual toItem:weakSelf.view attribute:NSLayoutAttributeCenterX multiplier:1.0f constant:0]];
        [weakSelf.view addConstraint:[NSLayoutConstraint constraintWithItem:view attribute:NSLayoutAttributeCenterY relatedBy:NSLayoutRelationEqual toItem:weakSelf.view attribute:NSLayoutAttributeCenterY multiplier:1.0f constant:0]];
       [weakSelf.view layoutIfNeeded];
                
        weakSelf.adView = view;
    }
    else {
        NSLog(@"Render did fail With error : %@", error);
    }
}];
```
</details>

<details>
<summary>Swift</summary>
```swift
let render = VANativeAdViewRender(nativeAd: nativeAd, customizedAdViewClass: SampleView1.self)
render.renderWithCompleteHandler({ [weak self] (view, error) in
    guard let safeSelf = self else {
        return
    }
                
    if let safeError = error {
        print("Render did fail With error : \(safeError)")
    }
    else if let safeView = view {
        safeSelf.view.addSubview(safeView)
                    
                // autolayout settings, fixed seize, vertical/horizontal center
        safeView.translatesAutoresizingMaskIntoConstraints = false
        safeView.addConstraint(NSLayoutConstraint(item: safeView, attribute: .Width, relatedBy: .Equal, toItem: nil, attribute: .NotAnAttribute, multiplier: 1.0, constant: CGRectGetWidth(safeView.bounds)))
        safeView.addConstraint(NSLayoutConstraint(item: safeView, attribute: .Height, relatedBy: .Equal, toItem: nil, attribute: .NotAnAttribute, multiplier: 1.0, constant: CGRectGetHeight(safeView.bounds)))
                    
        safeSelf.view.addConstraint(NSLayoutConstraint(item: safeView, attribute: .CenterX, relatedBy: .Equal, toItem: safeSelf.view, attribute: .CenterX, multiplier: 1.0, constant: 0))
        safeSelf.view.addConstraint(NSLayoutConstraint(item: safeView, attribute: .CenterY, relatedBy: .Equal, toItem: safeSelf.view, attribute: .CenterY, multiplier: 1.0, constant: 0))
        safeSelf.view.layoutIfNeeded()
                    
        safeSelf.adView = safeView
    }
})
```
</details>

You can see the ad in the center, even if the device is rotated. For details : [Objective-C](https://github.com/applauseadn/ios-sdk-demo/tree/master/ios-sdk-demo/ViewControllers/NativeAdSample1) / [Swift](https://github.com/applauseadn/ios-sdk-demo-swift/tree/master/ios-sdk-demo-swift/ViewControllers/NativeAdSample1)
