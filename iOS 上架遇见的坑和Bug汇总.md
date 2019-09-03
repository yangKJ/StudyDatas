#iOS 上架遇见的坑和Bug汇总

####ipa上传成功，但是iTunes Connect构建版本中却不显示
原因： iOS10以后，苹果要求对所有访问的私有权限进行描述，如访问相机、相册、电话簿、麦克风、定位等
解决方案： 
1、一般要等待5分钟左右，就会出现在构建版本位置处
2、若等待很久还是一直没有，则可能是info.plist里缺少类似使用相机的权限申请，这种情况会收到苹果的回复邮件，明确告诉你缺少哪个，修改好重新打包上传
>* 麦克风权限：Privacy - Microphone Usage Description 是否允许此App使用你的麦克风？
>* 相机权限： Privacy - Camera Usage Description 是否允许此App使用你的相机？
>* 相册权限： Privacy - Photo Library Usage Description 是否允许此App访问你的媒体资料库？
>* 通讯录权限： Privacy - Contacts Usage Description 是否允许此App访问你的通讯录？
>* 蓝牙权限：Privacy - Bluetooth Peripheral Usage Description 是否许允此App使用蓝牙？
>* 语音转文字权限：Privacy - Speech Recognition Usage Description 是否允许此App使用语音识别
>* 日历权限：Privacy - Calendars Usage Description 是否允许此App使用日历？
>* 定位权限：Privacy - Location When In Use Usage Description 我们需要通过您的地理位置信息获取您周边的相关数据
>* 定位权限：Privacy - Location Always Usage Description 我们需要通过您的地理位置信息获取您周边的相关数据

```
备注：使用定位功能`#import <CoreLocation/CoreLocation.h>`的时候，
本人遇见过需要两个定位权限都加入的情况，二者可以同时加入info.plist当中
<key>NSLocationWhenInUseUsageDescription</key>
<string>请允许使用您的位置，以便用户导航</string>
<key>NSLocationAlwaysUsageDescription</key>
<string>请允许使用您的位置，以便获取定位信息</string>
```
![WX20190528-142143@2x.png](https://upload-images.jianshu.io/upload_images/1933747-c0dc0cda872b3f01.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

> 一些关于审核的问题汇总：[https://xiaozhuanlan.com/iOSDeveloper](https://xiaozhuanlan.com/iOSDeveloper)

#### Xib报错
![WX20190731-141951@2x.png](https://upload-images.jianshu.io/upload_images/1933747-240f906e52f6931a.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)
解决方案：重启电脑，然后重启Xcode


#### Assets.xcassets报错
Failed to find a suitable device for the type IBSimDeviceTypeiPad2x (com.apple.dt.Xcode.IBSimDeviceType.iPad-2x) with runtime iOS 12.4 (12.4 - 16G73) - com.apple.CoreSimulator.SimRuntime.iOS-12-4
解决方案：Command + Shift + K 几次再重新 Command + R

####属性相关
最近遇见一个Bug，Debug模式下没问题，但是Release模式下就出现问题，外界Model有值但是传到另外一个控制器过去之后始终就是为nil
原因：再传递过去的属性set方法里面设置了数据，但是在viewDidLoad里面数据又被覆盖
解决方案1：不在set方法中去设置数据，在viewDidLoad设置了视图之后再去设置数据
解决方案2：重写这个属性的setter和getter方法，生成成员变量
```
@synthesize model = _model;
- (ActivitySignedModel*)model{
    return _model;
}
- (void)setModel:(ActivitySignedModel *)model{
    _model = model;
    self.titleLB.text = _model.activities_name;
}
```
解决方案3：写一个延时执行，不在set方法中做操作
```
[self performSelector:@selector(doSomething) withObject:nil afterDelay:.1f];
- (void)doSomething{
   NSLog(@"doSomething");
   self.titleLB.text = _model.activities_name;
}
```

####极光推送更换了BundleID之后、保存失败:Token Authentication 配置有误
解决网址：https://leancloud.cn/docs/ios_push_cert.html


####运行就崩，控制台打印如下信息
```
dyld: Library not loaded: @rpath/libswiftCore.dylib
  Referenced from: /var/containers/Bundle/Application/A81A055C-4D20-4F40-9EB1-76B2A93197CA/Winpower.app/Winpower
  Reason: no suitable image found.  Did find:
	/private/var/containers/Bundle/Application/A81A055C-4D20-4F40-9EB1-76B2A93197CA/Winpower.app/Frameworks/libswiftCore.dylib: code signature invalid for '/private/var/containers/Bundle/Application/A81A055C-4D20-4F40-9EB1-76B2A93197CA/Winpower.app/Frameworks/libswiftCore.dylib'
```
原因：名字重复使用过
解决方案：
1、退出 Xcode
2、重启电脑
3、找到 DerivedData 文件夹 删除 (路径:~/Library/Developer/Xcode/DerivedData)
4、删除 com.apple.dt.Xcode 文件 (路径:~/Library/Caches/com.apple.dt.Xcode)


####Application Loader无法登录提交
####Please sign in with an app-specific password. You can create one at appleid.apple.com
原因：账号开启了二次验证，也即双重验证
解决方案：
在[Apple官网](https://appleid.apple.com/account/manage)登陆你的账号，在管理密码的地方有一个Generate an App-Specific Password
用这个生成的密码在Xcode上登你的账号就行了，生成App专用密码
![image](http://upload-images.jianshu.io/upload_images/1933747-5d1b0d42c2707d84?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)


####iOS打包App到AppStore
####Authenticating with the app store上传卡顿
解决方案：打开终端
第一步：cd ~
第二步：mv .itmstransporter/ .old_itmstransporter/
第三步："/Applications/Xcode.app/Contents/Applications/Application Loader.app/Contents/itms/bin/iTMSTransporter"
第四步：等待更新完毕即可，然后再次打包App上传到AppStore

执行常见问题：
1.如果执行第二步报出文件路径已存在，删除该路径文件，使用命令sodu rm -r -f 文件名（删除文件）。然后再重新执行第二条命令。
2.如果执行第三步之后一段时间没有任何输入，不要犹豫，之间Control+c强行终止然后再执行第三步就行了

