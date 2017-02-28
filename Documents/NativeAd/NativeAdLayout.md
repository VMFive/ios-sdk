# 設計原生廣告 Layout
原生廣告的設計, 可以根據各 App UI 設計的不同, 客製化出需要的樣式, 下面將以 Demo App 中, `SampleView1` 這個樣式作為說明的範例

![](https://s3-ap-northeast-1.amazonaws.com/daidoujiminecraft/Daidouji/NativeAd1.gif)

在 `SampleView1` 中包含了三個元素如下
 - Video View (`UIView`)
 - Title Label (`UILabel`)
 - Call To Action Button (`UIButton`)

我們將依序的引導加入與 SDK 連動方式

## Implement Protocol
最初, 我們將 `VANativeAdViewRenderProtocol` 列入 `SampleView1` 實作項目

<details>
<summary>Objective-C</summary>
```objc
#import <VMFiveAdNetwork/VMFiveAdNetwork.h>

@interface SampleView1 : UIView <VANativeAdViewRenderProtocol>

@end
```
</details>

<details>
<summary>Swift</summary>
```swift
extension SampleView1: VANativeAdViewRenderProtocol {
}
```
</details>

## 影片顯示區域
接下來, 我們將 Video View 串上, `nativeVideoView` 為 `VANativeAdViewRenderProtocol` 中的一個 method, 
其中, 需要回傳一個 `UIView` 給 SDK

<details>
<summary>Objective-C</summary>
```objc
- (UIView *)nativeVideoView {
    return self.videoView;
}
```
</details>

<details>
<summary>Swift</summary>
```swift
func nativeVideoView() -> UIView {
    return self.videoView
}
```
</details>

## 主要顯示訊息
接著是 Title Label, `nativeTitleTextLabel` 會將目標 `UILabel` 填入 SDK 從 server 帶回來的值

<details>
<summary>Objective-C</summary>
```objc
- (UILabel *)nativeTitleTextLabel {
    return self.titleLabel;
}
```
</details>

<details>
<summary>Swift</summary>
```swift
func nativeTitleTextLabel() -> UILabel {
    return self.titleLabel
}
```
</details>

## 可變動字樣 CTA Button
最後是 Call To Action Button 的部分, 由於 `nativeCallToActionTextLabel` 需要我們回傳的是一個 `UILabel`, 
我們沒有辦法直接將 `UIButton` 直接給他, 所以這邊, 我們分成兩個步驟來做

### 接收 Server 字樣部分
我們先以一個 `UILabel` 來接收 Server 傳過來的字樣

<details>
<summary>Objective-C</summary>
```objc
- (UILabel *)nativeCallToActionTextLabel {
    return self.ctaLabel;
}
```
</details>

<details>
<summary>Swift</summary>
```swift
func nativeCallToActionTextLabel() -> UILabel {
    return self.ctaLabel
}
```
</details>

### 利用 KVO 特性 在收到變化時改變 Button 內容
然後在 `UILabel` 的 `text` 值變動的時候, 再通知我們的 `UIButton` 去做變更字樣的動作

<details>
<summary>Objective-C</summary>
```objc
#pragma mark - KVO

- (void)observeValueForKeyPath:(NSString *)keyPath ofObject:(id)object change:(NSDictionary<NSString *,id> *)change context:(void *)context {
    if ([keyPath isEqualToString:@"ctaLabel.text"]) {
        [self.ctaButton setTitle:change[@"new"] forState:UIControlStateNormal];
    }
}

#pragma mark - Life Cycle

- (id)initWithCoder:(NSCoder *)aDecoder {
    self = [super initWithCoder:aDecoder];
    if (self) {
        self.ctaLabel = [UILabel new];
        [self addObserver:self forKeyPath:@"ctaLabel.text" options:NSKeyValueObservingOptionNew context:nil];
    }
    return self;
}

- (void)dealloc {
    [self removeObserver:self forKeyPath:@"ctaLabel.text"];
}
```
</details>

<details>
<summary>Swift</summary>
```swift
// MARK: KVO
extension SampleView1 {
    
    override func observeValueForKeyPath(keyPath: String?, ofObject object: AnyObject?, change: [String : AnyObject]?, context: UnsafeMutablePointer<Void>) {
        if let safeChange = change, let newValue = safeChange["new"] as? String where keyPath == "ctaLabel.text" {
            self.ctaButton.setTitle(newValue, forState: .Normal)
        }
    }
    
}

// MARK: Life Cycle
class SampleView1: UIView {

    let ctaLabel = UILabel()
    
    required init?(coder aDecoder: NSCoder) {
        super.init(coder: aDecoder)
        self.addObserver(self, forKeyPath: "ctaLabel.text", options: .New, context: nil)
    }
    
    deinit {
        self.removeObserver(self, forKeyPath: "ctaLabel.text", context: nil)
    }
    
}
```
</details>

## nib 檔案連結與 CTA 元件設定
到這邊, 已經完整的將 `SampleView1` 的三個元素與 SDK 串起, 最後, 我們需要告訴 SDK, `SampleView1` 所對應的 nib 是哪一個, 以及可以觸發 Call To Action 的元件為哪一個

<details>
<summary>Objective-C</summary>
```objc
+ (UINib *)nibForAd {
    return [UINib nibWithNibName:@"SampleView1" bundle:nil];
}

- (NSArray *)clickableViews {
    return @[ self.ctaButton ];
}
```
</details>

<details>
<summary>Swift</summary>
```swift
static func nibForAd() -> UINib {
     return UINib.init(nibName: "SampleView1", bundle: nil)
}
    
func clickableViews() -> [AnyObject] {
    return [ self.ctaButton ]
}
```
</details>

到這邊已經完成了客製化的製作, 完整的檔案內容可以從 [Objective-C](https://github.com/VMFive/ios-sdk-demo/tree/master/ios-sdk-demo/Views/SampleView1) / [Swift](https://github.com/VMFive/ios-sdk-demo-swift/tree/master/ios-sdk-demo-swift/Views/SampleView1) 下載或是查看

## 備註
除了上述的內容之外 `VANativeAdViewRenderProtocol` 提供了多樣化的素材可以使用, 下面為完整可使用列表

```objc
// 回傳要展示標題文字
-(nonnull UILabel *)nativeTitleTextLabel;

// 回傳要展示說明文字
-(nonnull UILabel *)nativeMainTextLabel;

// 回傳要展示副標題
-(nonnull UILabel *)nativeSubtitleTextLabel;

// 回傳要要展示 CTA 文字
-(nonnull UILabel *)nativeCallToActionTextLabel;

// 回傳要展示說明文字
-(nonnull UITextField *)descriptionTextField;

// 回傳要顯示影片的 View
-(nonnull UIView *)nativeVideoView;

// 回傳主要圖片
-(nonnull UIImageView *)nativeMainImageView;

// 回傳 icon 圖片
-(nonnull UIImageView *)nativeIconImageView;

// 設定可以點擊的元素
-(nonnull NSArray *)clickableViews;

// 設定該 view 所使用的 nib 檔案
+(nonnull UINib *)nibForAd;
```
VMFive