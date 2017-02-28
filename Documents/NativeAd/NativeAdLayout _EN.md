# Native Ad Layout Design
You can customize the layout of ad to fit in your user interface. We will use `SampleView1` as an example to show you how to customize your own ad layout 

![](https://s3-ap-northeast-1.amazonaws.com/daidoujiminecraft/Daidouji/NativeAd1.gif)

In `SampleView1`, there are three elements 
 - Video View (`UIView`)
 - Title Label (`UILabel`)
 - Call To Action Button (`UIButton`)

## Implement Protocol
First, We will implement `VANativeAdViewRenderProtocol` in `SampleView1` 

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

## Video Player
Next, we will hook Video View to SDK. `nativeVideoView` is a method of `VANativeAdViewRenderProtocol` , 
and we need to return a`UIView` to SDK

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

## Title Text
For Title Label, `nativeTitleTextLabel` will fill `UILabel` with text that SDK receives from server. 

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

## CTA Button
Finally, for Call To Action Button , since `nativeCallToActionTextLabel` requires a `UILabel`, 
We cannot pass `UIButton` directly to it, we will seperate the implementation into 2 parts.

### Receive Text from Server 
We will use a `UILabel` to get text from server 

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

### Change the text of Button by KVO
When the value of text is changed in`UILabel`, we notify the button to change its text.

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

## Pass nib to SDK and assign Clickables 
Finally, we have to assign the nib file to SDK and the clickables.

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

Now we have finished the customization, you can check :[Objective-C](https://github.com/VMFive/ios-sdk-demo/tree/master/ios-sdk-demo/Views/SampleView1) / [Swift](https://github.com/VMFive/ios-sdk-demo-swift/tree/master/ios-sdk-demo-swift/Views/SampleView1) 

## Note
Other than the above contents ,`VANativeAdViewRenderProtocol`provides a variety of contents. Below are the complete creatives:

```objc
// Return Title Text
-(nonnull UILabel *)nativeTitleTextLabel;

// Return Main Text
-(nonnull UILabel *)nativeMainTextLabel;

// Return Subtitle Text
-(nonnull UILabel *)nativeSubtitleTextLabel;

// Return CTA Text
-(nonnull UILabel *)nativeCallToActionTextLabel;

// Return Description Text
-(nonnull UITextField *)descriptionTextField;

// Return Video View
-(nonnull UIView *)nativeVideoView;

// Return Main Image
-(nonnull UIImageView *)nativeMainImageView;

// Return Icon Image
-(nonnull UIImageView *)nativeIconImageView;

// Return Clickables
-(nonnull NSArray *)clickableViews;

// Return the nib for Ad
+(nonnull UINib *)nibForAd;
```
VMFive