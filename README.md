# iOS-SDK
- [概論](https://github.com/applauseadn/ios-sdk#概論)
- [安裝方法](https://github.com/applauseadn/ios-sdk#安裝方法)
- [Demos](https://github.com/applauseadn/ios-sdk#demos)
- [設計原生廣告 Layout](https://github.com/applauseadn/ios-sdk#設計原生廣告-layout)
* [載入並展示原生廣告](https://github.com/applauseadn/ios-sdk#載入並展示原生廣告)
* [在 TableView 中置入原生廣告](https://github.com/applauseadn/ios-sdk#在-tableview-中置入原生廣告)

## 概論
原生廣告沒有固定的規格大小，需要透過應用程式開發者的巧思將廣告的素材重新設計與編排後融合到使用者介面之中。

原生廣告帶來 **比傳統橫幅或是插頁廣告更友善的體驗與更好的成效**；

除此之外在原本的橫幅和插頁廣告版位外，可以在更多版位擺放廣告 **創造更多收入來源。**

**iOS SDK 完整支援 iOS 7.0 以上的裝置。**在這份文件中我們會詳細介紹，如何設計與排版原生廣告，並且利用 SDK 提供的 ```Render``` 機制產生原生廣告的 ```View```，並且利用 SDK 提供的 API 將原生廣告置入 ```TableView``` 中.

## 安裝方法
### CocoaPods
1. 在 `Podfile` 內加入 `pod 'VMFiveAdNetwork', '~> 2.1.2'`
2. 使用 `pod install` 安裝

### 手動
1. 下載最新版 [iOS SDK](https://github.com/applauseadn/ios-sdk/releases)
2. 解壓縮資料夾後, 在專案內選擇 `Add Files to YourProject`
<br>
<img src="https://raw.githubusercontent.com/applauseadn/ios-sdk/master/Images/%E8%9E%A2%E5%B9%95%E5%BF%AB%E7%85%A7%202016-05-12%20%E4%B8%8A%E5%8D%8810.02.14.png" width="289" height="226" />

3. 選擇 `VMFiveAdNetwork` 資料夾加入
<br>
<img src="https://raw.githubusercontent.com/applauseadn/ios-sdk/master/Images/%E8%9E%A2%E5%B9%95%E5%BF%AB%E7%85%A7%202016-05-12%20%E4%B8%8A%E5%8D%8810.08.51.png" width="258" height="251" />

4. 加入完成後, 從 `Xcode` 看起來會是
<br>
<img src="https://raw.githubusercontent.com/applauseadn/ios-sdk/master/Images/%E8%9E%A2%E5%B9%95%E5%BF%AB%E7%85%A7%202016-05-12%20%E4%B8%8A%E5%8D%8810.13.53.png" width="141" height="188" />

5. 然後我們在 `Build Phases` 中的 `Link Binary With Libraies` 加入下列的 frameworks
	* ```CoreMedia.framework```
	* ```CoreFoundation.framework```
	* ```AdSupport.framework```
	* ```CoreTelephony.framework```
	* ```CoreLocation.framework```
	* ```libz.tbd```
	* ```SystemConfiguration.framework```
	* ```AVFoundation.framework```
<br>
<img src="https://raw.githubusercontent.com/applauseadn/ios-sdk/master/Images/%E8%9E%A2%E5%B9%95%E5%BF%AB%E7%85%A7%202016-05-12%20%E4%B8%8A%E5%8D%8810.23.45.png" width="696" height="442" />

6. 在 `Build Settings` 中的 `Other Linker Flags` 加入 `-ObjC`
<br>
<img src="https://raw.githubusercontent.com/applauseadn/ios-sdk/master/Images/%E8%9E%A2%E5%B9%95%E5%BF%AB%E7%85%A7%202016-05-12%20%E4%B8%8A%E5%8D%8810.25.37.png" width="696" height="442" />

### plist 設定
**iOS 9 需要在 ```info.plist``` 裡面做以下修改，避免廣告請求失敗：**
```Objective-C
<key>NSAppTransportSecurity</key>
	<dict>
		<key>NSAllowsArbitraryLoads</key>
		<true/>
	</dict>
```
<br>
<img src="https://raw.githubusercontent.com/applauseadn/ios-sdk/master/Images/%E8%9E%A2%E5%B9%95%E5%BF%AB%E7%85%A7%202016-05-12%20%E4%B8%8A%E5%8D%8810.29.20.png" width="696" height="442" />

### 關閉 bitcode
在 `Build Settings` 中的 `Enable Bitcode` 設定為 `NO`
<br>
<img src="https://raw.githubusercontent.com/applauseadn/ios-sdk/master/Images/%E8%9E%A2%E5%B9%95%E5%BF%AB%E7%85%A7%202016-05-25%20%E4%B8%8A%E5%8D%8810.54.26.png" width="890" height="233" />

## Demos
未來所有的範例以及使用方法, 將移動至專案 [ios-sdk-demo](https://github.com/applauseadn/ios-sdk-demo),
或是 `Swift` 的版本 [ios-sdk-demo-swift](https://github.com/applauseadn/ios-sdk-demo-swift),
如果有任何串接上的問題, 也可以至 [Issue](https://github.com/applauseadn/ios-sdk-demo/issues) 中提出.

## 設計原生廣告 Layout
1. 設計原生廣告的 Layout，可以參考範例專案的 ```CustomView.xib```
2. 實作 ```VANativeAdViewRenderProtocol```，定義如下：：
    * ```-(nonnull UILabel *)nativeTitleTextLabel```：回傳要展示標題文字的 ```UILabel```
    * ```-(nonnull UILabel *)nativeMainTextLabel```：回傳要展示說明文字的 ```UILabel```
    * ```-(nonnull UILabel *)nativeSubtitleTextLabel```：回傳要展示副標題的 ```UILabel```
    * ```-(nonnull UILabel *)nativeCallToActionTextLabel```：回傳要要展示CTA文字的```UILabel```
    * ```-(nonnull UITextField *)descriptionTextField```：回傳要展示說明文字的 ```UITextField```
    * ```-(nonnull UIView *)nativeVideoView```：回傳 ```Video Player``` 的 ```View```
    * ```-(nonnull UIImageView *)nativeMainImageView```：回傳要展示 ```Main Image``` 的 ```UIImageView```
    * ```-(nonnull UIImageView *)nativeIconImageView```：回傳要展示 ```icon``` 的 ```UIImageView```
    * ```-(nonnull NSArray *)clickableViews```：回傳可以點擊的 ```View```，可以註冊多個 ```View``` 為可以點擊
    * ```+(nonnull UINib *)nibForAd```：回傳原生廣告的 ```Nib```

    範例：
    ```Objective-C
	/**
	 *  回傳擺放Title的Label
	 */
	-(UILabel *)nativeTitleTextLabel
	{
	    return _titleLabel;
	}
	
	/**
	 *  回傳擺放Icon的ImageView
	 */
	-(UIImageView *)nativeIconImageView
	{
	    return _iconView;
	}
	
	/**
	 *  回傳覆蓋Video View的UIView
	 *
	 *  @warning 這裡必須注意，若View的不符合Video的Aspect Ratio，則Video會以AspectFit的方式呈現（可能帶黑邊）
	 */
	-(UIView *)nativeVideoView
	{
	    return _videoView;
	}
    ```
3. 生成原生廣告的 ```Layout```，可以直接回傳 ```nib```:
     
     ```
	 +(UINib *)nibForAd
	{
	    return [UINib nibWithNibName:@"CustomView" bundle:nil];
	}
     ```


**完整的代碼可以參考可以參考範例專案的 ```VANativeAdViewProtocol.h``` 和 ```CustomView.m```**


## 載入並展示原生廣告
開始撰寫代碼之前，需要先引入以下的 Header 檔

```Objective-C
#import "VANativeAdViewRender.h" //SDK提供的header檔
#import "CustomView.h" // 對應原生廣告 xib 的 header 檔
#import "VANativeAd.h" //SDK提供的header檔
```

代碼需要實作 ```VANativeAdDelegate```,```VANativeAdViewRenderDelegate```
```Objective-C
@interface VideoNativeRenderViewController () <VANativeAdDelegate, VANativeAdViewRenderDelegate>
```

1. 創建```VANativeAd```，設定屬性並且載入廣告，需要傳入兩個參數：一個任意的字串作為後台出報表用的標示以及指定廣告類型，原生廣告請用```kVAAdTypeVideoCard```。

    填入正確的 ```API KEY``` 或是開啟測試模式後台才會投放廣告；**這裡要注意的是當測試模式開啟時無論有沒有填入正確的 ```API KEY``` 都只能取得沒有分潤的測試廣告**。 
    
    範例：
    
    ```Objective-C
	- (void)viewDidLoad {
	    [super viewDidLoad];
	    // Do any additional setup after loading the view.
	
	    // 建立 NativeAd 物件
	    _nativeAd = [[VANativeAd alloc] initWithPlacement:@"VMFiveAdNetwork_SampleApp_NativeRender" adType:kVAAdTypeVideoCard];
	    
	    _nativeAd.testMode = YES;
	    _nativeAd.apiKey = @"YOUR API KEY HERE";
	    _nativeAd.delegate = self;
	    
	    // 載入廣告
	    [_nativeAd loadAd];
	}
    ```
2. 實作 ```VANativeAdDelegate```，定義如下：
    * ```- (void)nativeAdDidLoad:(nonnull VANativeAd *)nativeAd;```：廣告素材已經成功載入，隨時可以展示。
    * ```- (void)nativeAd:(nonnull VANativeAd *)nativeAd didFailedWithError:(nonnull NSError *)error;```：載入廣告時出現錯誤.錯誤原因用錯誤代碼表示.
    * ```- (void)nativeAdDidClick:(nonnull VANativeAd *)nativeAd;```：廣告被點擊。
    * ```- (void)nativeAdDidFinishHandlingClick:(nonnull VANativeAd *)nativeAd;```：點擊觸發的動作已經處理完成。
    
    錯誤碼的定義如下：
    * ```VAErrorUnknown = 0```：不明的錯誤
    * ```VAErrorBadRequest=1```：原生廣告的參數無效或是錯誤
    * ```VAErrorNotRegistered```：沒有向SDK註冊原生廣告的View 
    * ```VAErrorNotLoaded```：原生廣告載入失敗
    * ```VAErrorBadNetwork```：沒有網路連線
    * ```VAErrorDownloadFailed```：廣告素材下載失敗
    * ```VAErrorBadView```：原生廣告的View是空的
    * ```VAErrorRegistered```：重複註冊了相同原生廣告的View
    * ```VAErrorWrongSize```：原生廣告的View大小不符合規範
    * ```VAErrorOSNotSupport```：iOS版本低於7.0無法播放影音廣告

3. 創建```VANativeAdViewRender```，展示原生廣告；需要傳入 ```nativeAd``` 物件與原生廣告 ```Layout``` 的 ```Classname```，然後呼叫 ```renderWithCompleteHandler``` 方法。 
    
    範例：
    ```Objective-C
    VANativeAdViewRender *render = [[VANativeAdViewRender alloc] initWithNativeAd:_nativeAd customizedAdViewClass:[CustomView class]];
[render renderWithCompleteHandler:^(UIView<VANativeAdViewRenderProtocol> *view, NSError *error){
            if (!error)
            {
                _adView = view;
                _adView.center = self.view.center;
                [self.view addSubview:_adView];
            }
            else
            {
                NSLog(@"Render did fail With error : %@", error);
            }
            
        }];
    ```	
    **要注意的是  ```VANativeAdViewRender ``` 必須要在廣告素材都已經載入後才能按照  ```VANativeAdViewRenderProtocol ``` 將素材展示；** 因此必須在廣告素材全部載入後再呼叫  ```renderWithCompleteHandler ``` 方法展示素材。
    
    例如範例專案中，我們就是在  ```nativeAdDidLoad ``` 這個  ```delegate ``` 中創建是  ```VANativeAdViewRender ``` 並且呼叫  ```renderWithCompleteHandler ``` 方法。

4. 釋放廣告資源
    ```Objective-C
    -(void)viewWillDisappear:(BOOL)animated
	{
	    [super viewWillDisappear:animated];
	    
	    [_nativeAd unloadAd];
	}
    ```

**有關 ```NativeAd``` 的詳細用法，可以參考範例專案中的 ```VideoNativeViewReder.m```**

## 在 TableView 中置入原生廣告
開始撰寫代碼之前，需要先引入以下的 Header 檔

```Objective-C
#import "VideoCardAdapterViewController.h"
#import "VAAdCellProvider.h"
#import "CustomView.h"
```

代碼需要實作 ```VAAdCellProviderDelegate```,```VAAdCellProviderDataSource```
```Objective-C
@interface VideoCardAdapterViewController () <UITableViewDataSource, UITableViewDelegate, VAAdCellProviderDelegate, VAAdCellProviderDataSource>
```

1. 建立原生廣告的 ```Attribute```，在 ```customAdViewClass``` 填入原生廣告 ```class name``` ：
  
    ```Objective-C
 VANativeAdViewAttributeObject *attribute = [[VANativeAdViewAttributeObject alloc] initWithContainer:_tableView];
 attribute.customAdViewClass = [CustomView class];
    ```	
2. 建立 ```AdCellProvider```
    ```Objective-C
 _adCellProvider = [[VAAdCellProvider alloc] initWithPlacement:@"VMFiveAdNetwork_SampleApp_CardAdapter" adType:kVAAdTypeVideoCard tableView:_tableView forAttributes:attribute];
    ```	
    
    參數定義如下 ：
    * ```initWithPlacement```:一個任意的字串作為廣告版位的名稱，這個名稱會在後台報表中的 ```Placement``` 欄位展示，可以根據這個字串在後台觀察廣告的成效。
    * ```adType```:指定原生廣告的類別，影音原生廣告請填 ```kVAAdTypeVideoCard```
    * ```tableView```:要插入原生廣告的 ```tableView```
    * ```forAttributes```:指定好原生廣告類別的 ```VANativeAdViewAttributeObject```

3. 設定 ```AdCellProvider``` 並且載入廣告，在載入廣告之前必須先填入正確的 ```API KEY```，或是開啟測試模式才能取得廣告。**要注意的是，App 上線前必須確定關閉測試模式。** 
    ```Objective-C
_adCellProvider.testMode = YES;
_adCellProvider.apiKey = @"your_key";
 [_adCellProvider loadAds];
    ```	
4. 實作 ```VAAdCellDataProvider```，設定每個 ```section``` 要插入的廣告總數，該 ```section``` 第一個廣告出現的 ```index```，以及廣告和廣告之間間隔的 ```row``` 數。
    
    ```VAAdCellDataProvider``` 定義如下 ：
    * ```-(NSUInteger)tableView:(nonnull UITableView *)tableView adStartRowInSection:(NSUInteger)section;```：在這個 ```delegate``` 裡面回傳 ```section``` 內廣告的起始位置。
    * ```-(NSUInteger)tableView:(nonnull UITableView *)tableView adOffsetInSection:(NSUInteger)section;```：在這個 ```delegate``` 裡面回傳 ```section``` 內的廣告間隔。
    * ```-(NSInteger)tableView:(nonnull UITableView *)tableView numberOfAdsInSection:(NSUInteger)section;```:在這個 ```delegate``` 裡面回傳一個 ```section``` 內要插入的廣告個數，如果要插入無限多個廣告則回傳 -1；若無實作此 ```delegate``` 則預設為無限插入廣告。

5. 實作 ```VAAdCellProvider```，接收 ```SDK``` 的事件。
    ```VAAdCellProvider``` 的定義如下：
    * ```-(void)adCellProvider:(nonnull VAAdCellProvider *)adCellProvider didFailWithError:(nonnull NSError *)error;```：當 ```adCellProvider``` 無法載入廣告時會發送這個事件，並且透過 ```Error``` 物件告知錯誤原因。
    * ```-(void)adCellDidLoadAtIndexPath:(nonnull NSIndexPath *)indexPath;```：當廣告成功載入時 ```SDK``` 會發送這個事件
    * ```-(void)adCellAtIndexPath:(nonnull NSIndexPath *)indexPath didFaislWithError:(nonnull NSError *)error;```：當某個 ```Cell``` 無法插入廣告時，```SDK``` 會發送這個事件並且告知發生錯誤的 ```index path``` 與錯誤原因。

    錯誤碼的定義如下：
    * ```VAErrorUnknown = 0```：不明的錯誤
    * ```VAErrorBadRequest=1```：原生廣告的參數無效或是錯誤
    * ```VAErrorNotRegistered```：沒有向SDK註冊原生廣告的View 
    * ```VAErrorNotLoaded```：原生廣告載入失敗
    * ```VAErrorBadNetwork```：沒有網路連線
    * ```VAErrorDownloadFailed```：廣告素材下載失敗
    * ```VAErrorBadView```：原生廣告的View是空的
    * ```VAErrorRegistered```：重複註冊了相同原生廣告的View
    * ```VAErrorWrongSize```：原生廣告的View大小不符合規範
    * ```VAErrorOSNotSupport```：iOS版本低於7.0無法播放影音廣告

**完整的代碼請參考範例專案中的 ```VideoCustomAdViewAdapterViewController.m```**
