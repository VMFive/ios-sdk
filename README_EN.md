# iOS-SDK
- [Introduction](https://github.com/VMFive/ios-sdk#introduction)
- [Install SDK](https://github.com/VMFive/ios-sdk#install-sdk)
- [Demos](https://github.com/VMFive/ios-sdk#demos)
- Native Ad
   - [Design Native Ad Layout](https://github.com/VMFive/ios-sdk/blob/master/Documents/NativeAd/NativeAdLayout_EN.md)
   - [Load and Show Native Ad](https://github.com/VMFive/ios-sdk/blob/master/Documents/NativeAd/UseNativeAd_EN.md)
   - [Insert Native Ad into TableView](https://github.com/VMFive/ios-sdk/blob/master/Documents/CellProvider/UseCellProvider_EN.md)

## Introduction

Native Ads do not require fixed layout and sizes. Application developers arrange the ad layout that best fit into the user interface.

Native Ads **bring more revenue and friendly user experience** then typical banners.

Besides the banners，developers can place ads in more places to **create more revenue**

**iOS SDK devices above iOS 7.0 **
## Install SDK
### CocoaPods
1. In `Podfile` , add `pod 'VMFiveAdNetwork', '~> 3.1.6'`
2. Use `pod install` to install SDK.

### Manually Install SDK
1. Download [iOS SDK](https://github.com/applauseadn/ios-sdk/releases)
2. Unzip the folder, in your project select `Add Files to YourProject`
<br>
<img src="https://raw.githubusercontent.com/applauseadn/ios-sdk/master/Images/%E8%9E%A2%E5%B9%95%E5%BF%AB%E7%85%A7%202016-05-12%20%E4%B8%8A%E5%8D%8810.02.14.png" width="289" height="226" />

3. Select `VMFiveAdNetwork` folder
<br>
<img src="https://raw.githubusercontent.com/applauseadn/ios-sdk/master/Images/%E8%9E%A2%E5%B9%95%E5%BF%AB%E7%85%A7%202016-05-12%20%E4%B8%8A%E5%8D%8810.08.51.png" width="258" height="251" />

4. After you install the SDK, your `Xcode` should looks like this :
<br>
<img src="https://raw.githubusercontent.com/applauseadn/ios-sdk/master/Images/%E8%9E%A2%E5%B9%95%E5%BF%AB%E7%85%A7%202016-05-12%20%E4%B8%8A%E5%8D%8810.13.53.png" width="141" height="188" />

5. In `Build Phases`, add the following framework in `Link Binary With Libraies`
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

6. In `Build Settings` ,`Other Linker Flags` add `-ObjC`
<br>
<img src="https://raw.githubusercontent.com/applauseadn/ios-sdk/master/Images/%E8%9E%A2%E5%B9%95%E5%BF%AB%E7%85%A7%202016-05-12%20%E4%B8%8A%E5%8D%8810.25.37.png" width="696" height="442" />

### plist settings
**iOS 9 requires the following settings in ```info.plist``` to avoid failing to load ad：**
```Objective-C
<key>NSAppTransportSecurity</key>
	<dict>
		<key>NSAllowsArbitraryLoads</key>
		<true/>
	</dict>
```
<br>
<img src="https://raw.githubusercontent.com/applauseadn/ios-sdk/master/Images/%E8%9E%A2%E5%B9%95%E5%BF%AB%E7%85%A7%202016-05-12%20%E4%B8%8A%E5%8D%8810.29.20.png" width="696" height="442" />

### disable bitcode
In `Build Settings` , set `Enable Bitcode` to `NO`
<br>
<img src="https://raw.githubusercontent.com/applauseadn/ios-sdk/master/Images/%E8%9E%A2%E5%B9%95%E5%BF%AB%E7%85%A7%202016-05-25%20%E4%B8%8A%E5%8D%8810.54.26.png" width="890" height="233" />

## Demos

 - [Objective-C Demo](https://github.com/applauseadn/ios-sdk-demo)
 - [Swift Demo](https://github.com/applauseadn/ios-sdk-demo-swift)
 - [Unity Demo](https://github.com/applauseadn/ios-sdk-demo-unity)

If you have any problems, you can write it in issue of each project
