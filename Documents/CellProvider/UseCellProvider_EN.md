# Place Native Ad in TableView 
We use `CellProviderSample1ViewController` to demonstrate `VAAdCellProvider` .This is a live demo. We use data from[臺北市開放認養動物](http://data.taipei/opendata/datalist/datasetMeta?oid=6a3e862a-e1cb-4e44-b989-d35609559463).

![](https://s3-ap-northeast-1.amazonaws.com/daidoujiminecraft/Daidouji/CellProvider2.gif)

`VAAdCellProvider` can be used in `UITableView` already with data . 
   * Create `VANativeAdViewAttributeObject`
   * Create `VAAdCellProvider`
   * Implement `VAAdCellProviderDataSource` 
   * Implement `VAAdCellProviderDelegate` 

## Create VANativeAdViewAttributeObject

`VANativeAdViewAttributeObject` is provided for setting layout, display size, and some other settings. We will use `SampleView1` again to demonstrate.

<details>
<summary>Objective-C</summary>
```objc
- (VANativeAdViewAttributeObject *)retrieveSampleView1Attributes {
    VANativeAdViewAttributeObject *attribute = [VANativeAdViewAttributeObject new];
    attribute.customAdViewClass = [SampleView1 class];
    attribute.customAdViewSizeHandler = ^(CGFloat width, CGFloat ratio) {
        CGFloat adWidth = CGRectGetWidth([UIScreen mainScreen].bounds);
        CGFloat adHeight = adWidth * ratio + 30.0f;
        return CGSizeMake(adWidth, adHeight);
    };
    return attribute;
}
```
</details>

<details>
<summary>Swift</summary>
```swift
private func retrieveSampleView1Attributes() -> VANativeAdViewAttributeObject {
    let attribute = VANativeAdViewAttributeObject()
    attribute.customAdViewClass = SampleView1.self
    attribute.customAdViewSizeHandler = { (width, ratio) in
        let adWidth = CGRectGetWidth(UIScreen.mainScreen().bounds);
        let adHeight = adWidth * ratio + 30.0;
        return CGSize(width: adWidth, height: adHeight);
    }
    return attribute
}
```
</details>

## Create VAAdCellProvider

Pass `VANativeAdViewAttributeObject` to `VAAdCellProvider`. `Placement` and `apiKey` need to be confirmed with sales personnel.

<details>
<summary>Objective-C</summary>
```objc
self.adCellProvider = [[VAAdCellProvider alloc] initWithPlacement:@"VMFiveAdNetwork_CellProviderSample1" adType:kVAAdTypeVideoCard tableView:self.tableView forAttributes:[self retrieveSampleView1Attributes]];
self.adCellProvider.testMode = YES;
self.adCellProvider.apiKey = @"YOUR API KEY";
[self.adCellProvider loadAds];
```
</details>

<details>
<summary>Swift</summary>
```swift
let adCellProvider = VAAdCellProvider(placement: "VMFiveAdNetwork_CellProviderSample1", adType: kVAAdTypeVideoCard, tableView: self.tableView, forAttributes: self.retrieveSampleView1Attributes())
adCellProvider.testMode = true
adCellProvider.apiKey = "YOUR API KEY"
adCellProvider.loadAds()
self.adCellProvider = adCellProvider
```
</details>

## Implement VAAdCellProviderDataSource to adjust ad position

We can `VAAdCellProviderDataSource` to set ad numbers, start positions,and ad frequency.
In `CellProviderSample1ViewController`, declare `<VAAdCellProviderDataSource>`

<details>
<summary>Objective-C</summary>
```objc
@interface CellProviderSample1ViewController : UIViewController <VAAdCellProviderDataSource>

@end
```
</details>

<details>
<summary>Swift</summary>
```swift
extension CellProviderSample1ViewController: VAAdCellProviderDataSource {
}
```
</details>

### Numbers of Ad
`tableView:numberOfAdsInSection:` Numbers of ad in a section  

`kVAAdCellProviderNumberOfAdsUnlimited` means unlimited numbers

`kVAAdCellProviderNumberOfAdsNotInsert` means no ad, or the number you want.

<details>
<summary>Objective-C</summary>
```objc
- (NSInteger)tableView:(UITableView *)tableView numberOfAdsInSection:(NSUInteger)section {
    return kVAAdCellProviderNumberOfAdsUnlimited;
}
```
</details>

<details>
<summary>Swift</summary>
```swift
func tableView(tableView: UITableView, numberOfAdsInSection section: UInt) -> Int {
    return kVAAdCellProviderNumberOfAdsUnlimited
}
```
</details>

### Ad start position
`tableView:adStartRowInSection:` The first index to show ad. For example, 0 means the very top of TableView.

<details>
<summary>Objective-C</summary>
```objc
- (NSUInteger)tableView:(UITableView *)tableView adStartRowInSection:(NSUInteger)section {
    return 4;
}
```
</details>

<details>
<summary>Swift</summary>
```swift
func tableView(tableView: UITableView, adStartRowInSection section: UInt) -> UInt {
    return 4
}
```
</details>

### Frequency
After the first ad, `tableView:adOffsetInSection:` you can set the cells between next ad.

<details>
<summary>Objective-C</summary>
```objc
- (NSUInteger)tableView:(UITableView *)tableView adOffsetInSection:(NSUInteger)section {
    return 8;
}
```
</details>

<details>
<summary>Swift</summary>
```swift
func tableView(tableView: UITableView, adOffsetInSection section: UInt) -> UInt {
    return 8
}
```
</details>

Now we finished setting `VAAdCellProviderDataSource`.

## Implement VAAdCellProviderDelegate 

`VAAdCellProviderDelegate` is used to notify SDK status and info to apps.  `CellProviderSample1ViewController` implements this protocol

<details>
<summary>Objective-C</summary>
```objc
@interface CellProviderSample1ViewController : UIViewController <VAAdCellProviderDataSource, VAAdCellProviderDelegate>

@end
```
</details>

<details>
<summary>Swift</summary>
```swift
extension CellProviderSample1ViewController: VAAdCellProviderDelegate {
}
```
</details>

Because `VAAdCellProviderDelegate` is mainly used to pass SDK information, you don't have to implement them all.

<details>
<summary>Objective-C</summary>
```objc
- (void)adCellProvider:(VAAdCellProvider *)adCellProvider didLoadAtIndexPath:(NSIndexPath *)indexPath {
    NSLog(@"%s %@", sel_getName(_cmd), indexPath);
}

- (void)adCellProvider:(VAAdCellProvider *)adCellProvider didFailWithError:(NSError *)error {
    NSLog(@"%s %@", sel_getName(_cmd), error);
}

- (void)adCellProvider:(VAAdCellProvider *)adCellProvider didFailAtIndexPath:(NSIndexPath *)indexPath withError:(NSError *)error {
    NSLog(@"%s %@, %@", sel_getName(_cmd), indexPath, error);
}

- (void)adCellProviderDidClick:(VAAdCellProvider *)adCellProvider {
    NSLog(@"%s", sel_getName(_cmd));
}

- (void)adCellProviderDidFinishHandlingClick:(VAAdCellProvider *)adCellProvider {
    NSLog(@"%s", sel_getName(_cmd));
}
```
</details>

<details>
<summary>Swift</summary>
```swift
func adCellProvider(adCellProvider: VAAdCellProvider, didLoadAtIndexPath indexPath: NSIndexPath) {
    print("\(#function) \(indexPath)")
}
    
func adCellAtIndexPath(indexPath: NSIndexPath, didFailWithError error: NSError) {
    print("\(#function) \(error)")
}
    
func adCellProvider(adCellProvider: VAAdCellProvider, didFailAtIndexPath indexPath: NSIndexPath, withError error: NSError) {
    print("\(#function) \(indexPath) \(error)")
}
    
func adCellProviderDidClick(adCellProvider: VAAdCellProvider) {
    print("\(#function)")
}
    
func adCellProviderDidFinishHandlingClick(adCellProvider: VAAdCellProvider) {
    print("\(#function)")
}
```
</details>

For details: [Objective-C](https://github.com/applauseadn/ios-sdk-demo/tree/master/ios-sdk-demo/ViewControllers/CellProviderSample1) / [Swift](https://github.com/applauseadn/ios-sdk-demo-swift/tree/master/ios-sdk-demo-swift/ViewControllers/CellProviderSample1)
