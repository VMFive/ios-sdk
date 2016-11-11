# iOS-SDK
- [概論](https://github.com/applauseadn/ios-sdk#概論)
- [安裝方法](https://github.com/applauseadn/ios-sdk#安裝方法)
- [Demos](https://github.com/applauseadn/ios-sdk#demos)
- 原生廣告
   - [設計原生廣告 Layout](https://github.com/applauseadn/ios-sdk/blob/master/Documents/NativeAd/NativeAdLayout.md)
   - [載入並展示原生廣告](https://github.com/applauseadn/ios-sdk/blob/master/Documents/NativeAd/UseNativeAd.md)
   - [在 TableView 中置入原生廣告](https://github.com/applauseadn/ios-sdk/blob/master/Documents/CellProvider/UseCellProvider.md)

## 概論
原生廣告沒有固定的規格大小，需要透過應用程式開發者的巧思將廣告的素材重新設計與編排後融合到使用者介面之中。

原生廣告帶來 **比傳統橫幅或是插頁廣告更友善的體驗與更好的成效**；

除此之外在原本的橫幅和插頁廣告版位外，可以在更多版位擺放廣告 **創造更多收入來源。**

**iOS SDK 完整支援 iOS 7.0 以上的裝置。**在這份文件中我們會詳細介紹，如何設計與排版原生廣告，並且利用 SDK 提供的 ```Render``` 機制產生原生廣告的 ```View```，並且利用 SDK 提供的 API 將原生廣告置入 ```TableView``` 中.

## 安裝方法
### CocoaPods
1. 在 `Podfile` 內加入 `pod 'VMFiveAdNetwork', '~> 3.0.2'`
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

 - [Objective-C Demo](https://github.com/applauseadn/ios-sdk-demo)
 - [Swift Demo](https://github.com/applauseadn/ios-sdk-demo-swift)
 - [Unity Demo](https://github.com/applauseadn/ios-sdk-demo-unity)

如果有任何串接上的問題, 也可以至各對應專案的 `issue` 中提出.
