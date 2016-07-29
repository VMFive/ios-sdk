Pod::Spec.new do |s|
  s.name         = "VMFiveAdNetwork"
  s.version      = "2.1.11"
  s.summary      = "Largest Native Video Ad Network in Taiwan."
  s.homepage     = "https://github.com/applauseadn/ios-sdk"
  s.license      = { :type => 'Commercial', :file => 'LICENSE.md' }
  s.author       = { "VM5" => "operator@vm5.com" }
  s.platform     = :ios, "7.0"
  s.source       = { :git => "https://github.com/applauseadn/ios-sdk.git", :tag => s.version.to_s }
  s.source_files = "VMFiveAdNetwork/VMFiveAdNetwork/*.h"
  s.vendored_libraries = "VMFiveAdNetwork/*.a"
  s.frameworks   = "CoreMedia", "CoreFoundation", "AdSupport", "CoreTelephony", "CoreLocation", "SystemConfiguration", "AVFoundation"
  s.libraries = 'z'
  s.requires_arc = true
end

