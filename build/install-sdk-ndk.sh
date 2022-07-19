#!/bin/bash

#wget https://dl.google.com/android/repository/commandlinetools-linux-8512546_latest.zip
mkdir android-sdk
cd android-sdk
unzip -q ../commandlinetools-*.zip 

#mv -v cmdline-tools tools
export ANDROID_SDK=$(pwd)
cd cmdline-tools/bin
./sdkmanager --update --sdk_root=$ANDROID_SDK
./sdkmanager --list --sdk_root=$ANDROID_SDK
./sdkmanager --install "build-tools;28.0.1" --sdk_root=$ANDROID_SDK
./sdkmanager --install platform-tools --sdk_root=$ANDROID_SDK
./sdkmanager --install "platforms;android-22" --sdk_root=$ANDROID_SDK
unset ANDROID_SDK

cd ../../..

#mv ./commandlinetools*.zip ./zip

#wget https://dl.google.com/android/repository/android-ndk-r25-linux.zip
unzip -q android-ndk*.zip

#mv ../android-ndk*.zip ./zip

mv *.zip ../

#if on ARM use this one instead
#wget https://github.com/android-ide/aide_ndk/releases/download/v20160121/android-ndk-aide-linux-arm-20160121.tar.bz2
#tar -xr android-ndk*.tar.bz2 ./

mv ./android-ndk-* ./android-ndk
cd android-ndk/build/tools
python make_standalone_toolchain.py --arch arm --api 22 --install-dir=android_toolchain_ARM_API22 




