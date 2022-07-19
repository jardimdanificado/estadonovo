#!/bin/bash
#cd .. 
#mkdir android
#cd android

wget https://dl.google.com/android/repository/commandlinetools-linux-8512546_latest.zip
mkdir android-sdk
cd android-sdk
unzip ../commandlinetools-linux*.zip ./
mv -v cmdline-tools tools
export ANDROID_SDK=$(pwd)
cd tools/bin
./sdkmanager --update --sdk_root=$ANDROID_SDK
./sdkmanager --list --sdk_root=$ANDROID_SDK
./sdkmanager --install "build-tools;28.0.1" --sdk_root=$ANDROID_SDK
./sdkmanager --install platform-tools --sdk_root=$ANDROID_SDK
./sdkmanager --install "platforms;android-22" --sdk_root=$ANDROID_SDK
unset ANDROID_SDK

cd ..

wget https://dl.google.com/android/repository/android-ndk-r25-linux.zip
unzip android-ndk*.zip ./

#if on ARM use this one instead VV
#wget https://github.com/android-ide/aide_ndk/releases/download/v20160121/android-ndk-aide-linux-arm-20160121.tar.bz2
#tar -xr android-ndk*.tar.bz2 ./

mv ./android-ndk* ./android-ndk
cd android-ndk/build/tools
Run python make_standalone_toolchain.py --arch arm --api 22 --install-dir=android_toolchain_ARM_API22 

cd..

mkdir ./toolchain_arm_api22 ./raylib ./estadonovo ./estadonovo/lib ./estadonovo/obj ./estadonovo/src ./estadonovo/dex ./estadonovo/res ./estadonovo/res/values ./estadonovo/assets ./src ./src/com ./src/com/jardimdanificado ./src/com/jardimdanificado/estadonovo/

cat <<EOF >./estadonovo/obj
<?xml version="1.0" encoding="utf-8"?>
<resources>
    <string name="app_name">Estado Novo</string>
</resources>
EOF

cat <<EOF >./src/com/estadonovo/estadonovo/NativeLoader.java
package com.jardimdanificado.estadonovo; 
public class NativeLoader extends android.app.NativeActivity { 
    static {
        System.loadLibrary("maquina"); // must match name of shared library (in this case libmaquina.so) 
    } 
} 
EOF

cat <<EOF >./estadonovo/AndroidManifest.xml
<?xml version='1.0' encoding="utf-8" ?>
<manifest xmlns:android="http://schemas.android.com/apk/res/android" package='com.jardimdanificado.estadonovo' android:versionCode='0'
    android:versionName='0' >
    <application>
        <activity android:name="com.jardimdanificado.estadonovo.NativeLoader"
            android:theme="@android:style/Theme.NoTitleBar.Fullscreen"
            android:configChanges="orientation|keyboardHidden|screenSize"
            android:launchMode="singleTask"
            android:clearTaskOnLaunch="true">
        <meta-data android:name="android.app.maquina" android:value="estadonovo"/>
            <intent-filter>
                <category android:name='android.intent.category.LAUNCHER'/>
                <action android:name='android.intent.action.MAIN'/>
            </intent-filter>
        </activity>
    </application>
    <supports-screens android:anyDensity="true"/>
</manifest>

