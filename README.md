[源码传送门](https://github.com/atove/AstraMD5)
# AstraHttp
在原生层进行二次打包校验及MD5加密，有效防止反编译、二次打包。    
![效果图](http://upload-images.jianshu.io/upload_images/5088149-462e307d4230e542.gif?imageMogr2/auto-orient/strip%7CimageView2/2/w/400 )

>**二次打包校验原理：**   
在原生层获取应用包名及签名文件hash值，并与正确的值进行比对。

##如何使用
因为每个项目都不同，需要根据自己需要改源码，所以就不提供 gradle 引入方式了。   
将[源码](https://github.com/atove/AstraMD5) download 下来，然后把其中的 md5jni 引入到自己的项目中，找到 signaturecheck.h 文件把 *app_packageName 修改成自己的包名，把 app_signature_hash_code 修改成自己的 hashcode 。
```
//合法的APP包名
static const char *app_packageName = "com.astra.md5.simple";
//合法的hashcode 1154605269:这个值是我生成的这个可以store文件的hash值
static const int app_signature_hash_code = 1154605269;
```
在 JNIHLSign.c 文件中修改：
```
static const char MD5_KEY[] = "xxx";
```
及
```
//拼接的待加密字符串，可以根据自身需求修改
sprintf(buffer, "%s%s%d", szText, MD5_KEY, hashCode);
```
以实现符合自身要求的加密方式。

#####调用：
```
SignTool.sign(MainActivity.this, unSignText);
```

##最后
当代码调试成功后，就可以生成 aar 了。   
你的项目运行过后在 md5jni/build/outputs/aar 下会生成 aar 文件，就可以直接拿过来用了，并且可以将 md5jni 模块移除了，找到 gradle.properties 文件，把
```
android.useDeprecatedNdk=true
```
注掉，这样就能提高开发编译速度，并且提高 debug 速度。
