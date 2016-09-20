# 在 TableView 中置入原生廣告
在這邊我們用 `CellProviderSample1ViewController` 來展示 `VAAdCellProvider` 使用的效果, 這是一個活潑的範例, 利用 [臺北市開放認養動物](http://data.taipei/opendata/datalist/datasetMeta?oid=6a3e862a-e1cb-4e44-b989-d35609559463) 提供的資料,
可以一邊看 Demo, 一邊看是不是有想要領養的動物

![](https://s3-ap-northeast-1.amazonaws.com/daidoujiminecraft/Daidouji/CellProvider2.gif)

`VAAdCellProvider` 可以使用在已經建立好資料的 `UITableView` 上, 對於已經存在的 code, 不需要有太多的改變
   * 建立 `VANativeAdViewAttributeObject`
   * 建立 `VAAdCellProvider`
   * 實作 `VAAdCellProviderDataSource` 調整需要顯示的位置
   * 實作 `VAAdCellProviderDelegate` 接收來自 SDK 的訊息

## 建立 VANativeAdViewAttributeObject

`VANativeAdViewAttributeObject` 可以提供我們設定要使用的 layout, 顯示出來的大小, 跟一些相關的配置, 
這邊我們一樣用我們熟悉的 `SampleView1`

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

## 建立 VAAdCellProvider

將我們上面建立的 `VANativeAdViewAttributeObject` 填入 `VAAdCellProvider` 中, 其中的 `Placement` 與 `apiKey`, 請與接洽之業務取得

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

## 實作 VAAdCellProviderDataSource 調整需要顯示的位置

我們可以透過 `VAAdCellProviderDataSource` 來設置, 廣告出現的數量, 廣告出現的起始位置, 以及廣告每間隔多少個出現一次,
先將我們的 `CellProviderSample1ViewController` 加上 `<VAAdCellProviderDataSource>`

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

### 插入廣告數量
`tableView:numberOfAdsInSection:` 可以回傳我們要在當前的 tableview 中, 插入幾個廣告 `kVAAdCellProviderNumberOfAdsUnlimited` 為無限 `kVAAdCellProviderNumberOfAdsNotInsert` 為不插入, 或是設置一個期望的數量, 這邊我們假設不限制廣告出現的數目

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

### 廣告出現起始位置
`tableView:adStartRowInSection:` 可以調整廣告由哪一個 index 開始出現, 比方設 0, 則會出現在整個 tableview 的最頂端, 設 4 則會從 index 4 開始出現

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

### 插入廣告間隔
出現了第一個廣告後, `tableView:adOffsetInSection:` 可以設定每間隔多少個 cell, 會再出現下一個廣告

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

到這邊, 我們已經將 `VAAdCellProviderDataSource` 的部分設置完成.

## 實作 VAAdCellProviderDelegate 接收來自 SDK 的訊息

`VAAdCellProviderDelegate` 大部分是提示 SDK 發生的行為, 比方說已經填入廣告, 或是填入廣告失敗等等... 我們一樣先讓這個 `CellProviderSample1ViewController` implement 這個 protocol

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

由於 `VAAdCellProviderDelegate` 主要為帶回訊息, 可以依照各 app 的需求, 取用需要的部份, 這邊只列出各個回傳訊息, 不一一累述

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

這個部分詳細的 Demo 可以參考 [Objective-C](https://github.com/applauseadn/ios-sdk-demo/tree/master/ios-sdk-demo/ViewControllers/CellProviderSample1) / [Swift](https://github.com/applauseadn/ios-sdk-demo-swift/tree/master/ios-sdk-demo-swift/ViewControllers/CellProviderSample1)
