# iOS-SDK
- [概論](https://github.com/weitingboy/android-sdk#概論)
- [導入 SDK](https://github.com/weitingboy/android-sdk#導入-sdk)
- [設計原生廣告 Layout](https://github.com/weitingboy/android-sdk#卡片型原生影音廣告)
* [載入並展示原生廣告](https://github.com/weitingboy/android-sdk#listview-型原生影片廣告)
* [在 TableView 中置入原生廣告](https://github.com/weitingboy/android-sdk#影音插頁廣告interstitial)

## 概論
原生廣告沒有固定的規格大小，需要透過應用程式開發者的巧思將廣告的素材重新設計與編排後融合到使用者介面之中。

原生廣告帶來 **比傳統橫幅或是插頁廣告更友善的體驗與更好的成效**；

除此之外在原本的橫幅和插頁廣告版位外，可以在更多版位擺放廣告 **創造更多收入來源。**

**iOS SDK 完整支援 iOS 7.0 以上的裝置。**在這份文件中我們會詳細介紹，如何設計與排版原生廣告，並且利用 SDK 提供的 ```Render``` 機制產生原生廣告的 ```View```，並且利用 SDK 提供的 API 將原生廣告置入 ```TableView``` 中.

## 導入 SDK
1. 下載此專案中最新版 iOS SDK
2. 將 SDK 的資料夾拖拉到您的 Xcode 的專案中**(建議放在專案目錄下)**
3. 在 ```Build Phases``` 中的 ```Link Binary with Libraries``` 中加入 ```libVMFiveAdNetwork.a``` 與下列的 ```framwork``` 和 ```.tbd```
    * ```CoreMedia.framework```
    * ```CoreFoundation.framework```
    * ```AdSupport.framework```
    * ```CoreTelephony.framework```
    * ```CoreLocation.framework```
        * ```libVMFiveAdNetwork.a```
        * ```libz.tbd```
    * ```SystemConfiguration.framework```
    * ```AVFoundation.framework```
4. 在 ```Copy Bundle Resource``` 中加入 ```vres.zip```
5. 在 ```Build Settings``` 中的 ```Other Link Flag``` 加入 -ObjC

**iOS 9 需要在 ```info.plist``` 裡面做以下修改，避免廣告請求失敗：**
```Objective-C
<key>NSAppTransportSecurity</key>
	<dict>
		<key>NSAllowsArbitraryLoads</key>
		<true/>
	</dict>
```

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
開始撰寫代碼之前，需要先引入以下的物件，完整的程式碼請參考 ```ExampleNative.java```

```java
import com.core.adnsdk.AdObject;
import com.core.adnsdk.CardAdRenderer;
import com.core.adnsdk.CardViewBinder;
import com.core.adnsdk.ErrorMessage;
import com.core.adnsdk.AdViewType;
import com.core.adnsdk.NativeAdAdapter;
import com.core.adnsdk.AdPoolListener;
```

1. 新增一個 ```CardViewBinder``` 物件，將 ```Layout``` 裡的 UI 元件 id 透過 ```CardViewBinder``` 與綁定廣告素材的關聯與規則
    
    範例：
    ```java
    CardViewBinder vBinder = new CardViewBinder.Builder(R.layout.custom_video_ad_list_item)
       .loadingId(R.id.native_loading_image)
       .mainImageId(R.id.native_main_image)
       .titleId(R.id.native_title)
       .videoPlayerId(R.id.native_video_layout)
       .iconImageId(R.id.native_icon_image)
       .callToActionId(R.id.native_cta)
       .build();
    ```


## 在TableView中置入原生廣告

1. 在開始撰寫程式碼之前,請先在 ```AndroidManifest.xml``` 中宣告插頁廣告的 ```Actitivity ```
    * 直屏的 ```Activity```：
  
    ```java
    <activity
   android:name="com.core.adnsdk.InterstitialActivity"
   android:configChanges="keyboard|keyboardHidden|orientation|screenLayout|uiMode|screenSize|smallestScreenSize"
   android:hardwareAccelerated="true">
    </activity>
    ```
    * 轉橫屏全螢幕播放的 ```Activity```:
  
    ```java
    <activity
   android:name="com.core.adnsdk.FullScreenVideoActivity"
   android:configChanges="keyboard|keyboardHidden|orientation|screenLayout|uiMode|screenSize|smallestScreenSize"
   android:screenOrientation="landscape"
   android:hardwareAccelerated="true">
    </activity>
    ```
