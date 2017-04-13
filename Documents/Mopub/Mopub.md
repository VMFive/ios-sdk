# Mopub
這個段落可以幫助您使用 `Mopub` 聯播網串接時的流程與方法

## 串接前準備
* 已經先用 `CocoaPod` 或是手動的方式安裝好 `VMFiveAdNetwork`
* 已經先用 `CocoaPod` 或是手動的方式安裝好 `mopub-ios-sdk`
* 從 [發布版本](https://github.com/VMFive/ios-sdk/releases) 中, 下載最新版本的壓縮包裝, 以下圖為例, 請下載 `3.1.1.zip`

![](https://s3-ap-northeast-1.amazonaws.com/daidoujiminecraft/Daidouji/%E8%9E%A2%E5%B9%95%E5%BF%AB%E7%85%A7+2017-03-15+%E4%B8%8A%E5%8D%8811.25.34.png)

* 將下載下來的包裝解壓後, 可以看到如下的檔案結構

![](https://s3-ap-northeast-1.amazonaws.com/daidoujiminecraft/Daidouji/%E8%9E%A2%E5%B9%95%E5%BF%AB%E7%85%A7+2017-03-15+%E4%B8%8A%E5%8D%8811.31.49.png)

## 串接流程
* 我們以 [iOS Demo](https://github.com/VMFive/ios-sdk-demo) 為例, 我們將 `VMFiveMoPubAdapter` 整個資料夾, 擺放至專案內

![](https://s3-ap-northeast-1.amazonaws.com/daidoujiminecraft/Daidouji/%E8%9E%A2%E5%B9%95%E5%BF%AB%E7%85%A7+2017-03-15+%E4%B8%8A%E5%8D%8811.37.09.png)

* 接下來, 我們需要讓 `mopub-ios-sdk` 知道 `VMFiveAdNetwork` 的存在, 先利用 `Xcode` 的搜尋功能, 找到檔案 `MOPUBNativeVideoAdRenderer.m`

![](https://s3-ap-northeast-1.amazonaws.com/daidoujiminecraft/Daidouji/%E8%9E%A2%E5%B9%95%E5%BF%AB%E7%85%A7+2017-03-15+%E4%B8%8A%E5%8D%8811.42.45.png)

* 點擊 `MOPUBNativeVideoAdRenderer.m`, 在這個檔案中搜尋 `rendererConfigurationWithRendererSettings:` 這個 Method

![](https://s3-ap-northeast-1.amazonaws.com/daidoujiminecraft/Daidouji/%E8%9E%A2%E5%B9%95%E5%BF%AB%E7%85%A7+2017-03-15+%E4%B8%8A%E5%8D%8811.46.09.png)

* 我們會看到, 目前 `config.supportedCustomEvents` 中只有一個內容是 `MOPUBNativeVideoCustomEvent`, 我們幫他加上一個新的內容名稱為 `VMFiveNativeVideoCustomEvent`, 如下圖

![](https://s3-ap-northeast-1.amazonaws.com/daidoujiminecraft/Daidouji/%E8%9E%A2%E5%B9%95%E5%BF%AB%E7%85%A7+2017-03-15+%E4%B8%8A%E5%8D%8811.49.51.png)

## 串接上可能會遇到的問題

### Swift 找不到 SDK 相關檔案
請在專案的 `Build Setting` 中設定 `Objective-C Bridging Header` 如圖

![](https://s3-ap-northeast-1.amazonaws.com/daidoujiminecraft/Daidouji/%E8%9E%A2%E5%B9%95%E5%BF%AB%E7%85%A7+2017-04-13+%E4%B8%8B%E5%8D%881.59.18.png)

檔案的內容可參考 [Bridging.h](https://github.com/VMFive/ios-sdk-demo-swift/blob/feature/fix_for_swift3/ios-sdk-demo-swift/Bridging.h)

### Swift 中 @import mopub_ios_sdk; 出現錯誤
根據 `Mopub` 版本不同, build 出來的 framework 名稱會有所差異, 舊版本可能會叫 `mopub_ios_sdk`, 新版本目前叫 `MoPub`, 至於到底要用什麼名字才是正確的, 可以從 `Pods/Products` 中確認, 如圖

![](https://s3-ap-northeast-1.amazonaws.com/daidoujiminecraft/Daidouji/%E8%9E%A2%E5%B9%95%E5%BF%AB%E7%85%A7+2017-04-13+%E4%B8%8B%E5%8D%882.06.57.png)

## 設定 Mopub 網頁

在建立廣告時, 請將下面兩個欄位填入相對應的內容

* 在 `CUSTOM EVENT CLASS` 的部分填入 `VMFiveNativeVideoCustomEvent`
* 在 `CUSTOM EVENT CLASS DATA` 的部分填入 `{ "testMode": 1, "placement": "yourplacement", "apiKey":"yourapikey" }`

其中
```javascript
{ 
	"testMode": 1, 
	"placement": "yourplacement", 
	"apiKey": "yourapikey" 
}
```
`testMode` 需要正式廣告時請切換成 0
## App 內串接
請從 [Objective-C 範例](https://github.com/VMFive/ios-sdk-demo/tree/master/ios-sdk-demo/ViewControllers/MoPubNativeAdSample) / [Swift 範例](https://github.com/VMFive/ios-sdk-demo-swift/tree/feature/fix_for_swift3/ios-sdk-demo-swift/ViewControllers/MoPubNativeAdSample) 作為參考
