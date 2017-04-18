# 載入並展示原生廣告
在上一個章節中, 我們已經成功的建立了 `SampleView1` 可供使用, 在這邊, 會以 `NativeAdSample1ViewController` 當作範例, 
說明接下來將 `NativeAd` 如何呈現至 `UIViewController` 的後續動作

![](https://s3-ap-northeast-1.amazonaws.com/daidoujiminecraft/Daidouji/NativeAd1.gif)

這部分的串接有四個重點
 * 使用 `NativeAd` 做廣告請求
 * 利用 `VANativeAdDelegate` 得知廣告是否接收成功
 * 使用 `VANativeAdViewRender` 將廣告素材繪製至 `SampleView1`
 * 調整生成的 `SampleView1` 至指定位置
 
## 廣告請求
首先我們需要利用 `VANativeAd` 透過 SDK, 與 server request 相對應的廣告內容下來, 並在 `viewWillAppear:` 時做 `loadAd`, 
在 `viewWillDisappear:` 時做 `unloadAd`

建立 `VANativeAd` 時, 有兩個需要填入的參數

 * placement 為向 `Applause` 申請廣告串接時, 由業務人員分配的一組代碼
 * adType 在使用原生廣告時, 請填入 `kVAAdTypeVideoCard`
 
完成之後, 可以選擇設定 `testMode` 為 `YES` 使用測試模式, 或設定為 `NO` 關閉測試模式, 
**在正式上線時, 請務必將測試模式關閉, 以及項業務人員取得正確之 API Key, 以確保獲得廣告分潤金額**

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

    // 建立NativeAd物件做為Render的Ad資料來源
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

如果上面有注意到的話, 我們有將 `NativeAd` 的 delegate 指向 self 本身, 所以我們必須先告知當前的 class, 
我們將要實作這個項目

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

然後我們開始實作 `VANativeAdDelegate` 

<details>
<summary>Objective-C</summary>

```objc
#pragma mark - VANativeAdDelegate

// 當廣告素材準備完畢時
- (void)nativeAdDidLoad:(VANativeAd *)nativeAd {
    NSLog(@"%s", sel_getName(_cmd));
}

// 當有任何不正確發生時, 從 error 顯示的內容, 可以知道錯誤的原因
// 如有任何問題, 可與 FAE 或是開發人員聯繫
- (void)nativeAd:(VANativeAd *)nativeAd didFailedWithError:(NSError *)error {
    NSLog(@"%s %@", sel_getName(_cmd), error);
}

// 當廣告被點擊時 (離開 App 前)
- (void)nativeAdDidClick:(VANativeAd *)nativeAd {
    NSLog(@"%s", sel_getName(_cmd));
}

// 當點擊廣告後, 回到 App 時 (進入 App 後)
- (void)nativeAdDidFinishHandlingClick:(VANativeAd *)nativeAd {
    NSLog(@"%s", sel_getName(_cmd));
}

// 廣告已成功地被 Impression
-(void)nativeAdBeImpressed:(VANativeAd *)nativeAd {
    NSLog(@"%s", sel_getName(_cmd));
}

// 廣告播放完畢
- (void)nativeAdDidFinishImpression:(VANativeAd *)nativeAd {
    NSLog(@"%s", sel_getName(_cmd));
}
```

</details>
<details>
<summary>Swift</summary>

```swift

// 當廣告素材準備完畢時
func nativeAdDidLoad(nativeAd: VANativeAd) {
    print("\(#function)")
}
    
// 當有任何不正確發生時, 從 error 顯示的內容, 可以知道錯誤的原因
// 如有任何問題, 可與 FAE 或是開發人員聯繫
func nativeAd(nativeAd: VANativeAd, didFailedWithError error: NSError) {
    print("\(#function) \(error)")
}
    
// 當廣告被點擊時 (離開 App 前)
func nativeAdDidClick(nativeAd: VANativeAd) {
    print("\(#function)")
}
    
// 當點擊廣告後, 回到 App 時 (進入 App 後)
func nativeAdDidFinishHandlingClick(nativeAd: VANativeAd) {
    print("\(#function)")
}
    
// 廣告已成功地被 Impression
func nativeAdBeImpressed(nativeAd: VANativeAd) {
    print("\(#function)")
}
    
// 廣告播放完畢
func nativeAdDidFinishImpression(nativeAd: VANativeAd) {
    print("\(#function)")
}
```

</details>

delegate 的部分並非全部都需要 implement, 可以依照各 App 的不同, 選擇接收不同的事件

## 利用 VANativeAdViewRender 繪製至 SampleView1

好囉, 如果我們順利的進入了 `nativeAdDidLoad:` 後, 我們就可以開始將素材 render 到我們指定的 view 中, 
建立 `VANativeAdViewRender` 時需要填入兩個參數

 * load 好資源的 nativeAd
 * custom ad 的 layout (在這邊的話指的是 SampleView1)
 
完成之後使用 `renderWithCompleteHandler:` 開始 render, 可以透過回傳的 `error` 參數知道是否 render 成功

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

## 擺放至指定位置

在這個範例中, 我們預期的效果是將廣告置中擺放, 在不同的 App 中, 可以依照任何想要方式擺放

<details>
<summary>Objective-C</summary>

```objc
VANativeAdViewRender *render = [[VANativeAdViewRender alloc] initWithNativeAd:nativeAd customizedAdViewClass:[SampleView1 class]];
        
__weak NativeAdSample1ViewController *weakSelf = self;
[render renderWithCompleteHandler: ^(UIView<VANativeAdViewRenderProtocol> *view, NSError *error) {
            
    if (!error) {
        [weakSelf.view addSubview:view];
                
        // autolayout 設定, 固定大小, 水平垂直置中
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
                    
        // autolayout 設定, 固定大小, 水平垂直置中
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

順利的話, 就可以看見廣告呈現在畫面中央, 即使手機旋轉, 依然可以保持置中, 詳細的 Demo 可以參考 [Objective-C](https://github.com/VMFive/ios-sdk-demo/tree/master/ios-sdk-demo/ViewControllers/NativeAdSample1) / [Swift](https://github.com/VMFive/ios-sdk-demo-swift/tree/master/ios-sdk-demo-swift/ViewControllers/NativeAdSample1)
