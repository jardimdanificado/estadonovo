mkdir ./estadonovo ./estadonovo/lib ./estadonovo/lib/armv8-a ./estadonovo/obj ./estadonovo/src ./estadonovo/dex ./estadonovo/res ./estadonovo/res/values ./estadonovo/assets ./src ./src/com ./src/com/jardimdanificado ./src/com/jardimdanificado/estadonovo/

#change those to YOUR sdk/ndk path
export NDK=/home/jardel/android-build/android-ndk
export ASDK=/home/jardel/android-build/android-sdk

python3 $NDK/build/tools/make_standalone_toolchain.py --arch arm64 --api 22 --install-dir=android_toolchain_ARM_API22

cp -r ../../src ./estadonovo/

touch ./estadonovo/res/values/strings.xml
cat <<EOF >./estadonovo/res/values/strings.xml
<?xml version="1.0" encoding="utf-8"?>
<resources>
    <string name="app_name">Estado Novo</string>
</resources>
EOF

touch ./src/com/jardimdanificado/estadonovo/NativeLoader.java
cat <<EOF >./src/com/jardimdanificado/estadonovo/NativeLoader.java
package com.jardimdanificado.estadonovo;
public class NativeLoader extends android.app.NativeActivity { 
    static {
        System.loadLibrary("estadonovo"); // must match name of shared library (in this case libestadonovo.so) 
    } 
} 
EOF

touch ./estadonovo/AndroidManifest.xml
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
        <meta-data android:name="android.app.estadonovo" android:value="estadonovo"/>
            <intent-filter>
                <category android:name='android.intent.category.LAUNCHER'/>
                <action android:name='android.intent.action.MAIN'/>
            </intent-filter>
        </activity>
    </application>
    <supports-screens android:anyDensity="true"/>
</manifest>
EOF

cd estadonovo 

cp ../../libs/android-arm64/libraylib.a lib/armv8-a/libraylib.a
keytool -genkeypair -validity 1000 -dname "CN=seth,O=Android,C=ES" -keystore estadonovo.keystore -storepass 'whatever' -keypass 'whatever' -alias projectKey -keyalg RSA

touch ./build.sh
cat <<EOF >./build.sh
../android_toolchain_ARM_API22/bin/aarch64-linux-android-gcc -c -I/usr/include/ $NDK/sources/android/native_app_glue/android_native_app_glue.c -o obj/native_app_glue.o -std=c99 -march=armv8-a  -mfpu=vfpv3-d16 -ffunction-sections -funwind-tables -fstack-protector-strong -fPIC -Wall -Wa,--noexecstack -Wformat -Werror=format-security -no-canonical-prefixes -DANDROID -DPLATFORM_ANDROID -D__ANDROID_API__=22 

# Requires: folder setup
# Creates: obj/native_app_glue.o
# Note: This gcc uses other tools in the same toolchain folder structure, don't even thing about symlinking to it.

../android_toolchain_ARM_API22/bin/aarch64-linux-android-ar rcs obj/libnative_app_glue.a obj/native_app_glue.o

# Requires: obj/native_app_glue.o
# Creates: obj/libnative_app_glue.a

../android_toolchain_ARM_API22/bin/aarch64-linux-android-gcc -c ./src/estadonovo.c -o obj/estadonovo.o -I/usr/include/ -I./src/maquina/raylib -I$NDK/sources/android/native_app_glue -std=c99 -march=armv8-a  -mfpu=vfpv3-d16 -ffunction-sections -funwind-tables -fstack-protector-strong -fPIC -Wall -Wa,--noexecstack -Wformat -Werror=format-security -no-canonical-prefixes -DANDROID -DPLATFORM_ANDROID -D__ANDROID_API__=22 --sysroot=../toolchain_ARM_API22/sysroot

# Requires: estadonovo.c
# Creates: obj/estadonovo.o

../android_toolchain_ARM_API22/bin/aarch64-linux-android-gcc -o lib/armeabi-v8a/libestadonovo.so obj/estadonovo.o -shared -I. -I/usr/include/ -I./src/maquina/raylib -I$NDK/sources/android/native_app_glue -Wl,-soname,libestadonovo.so -Wl,--exclude-libs,libatomic.a -Wl,--build-id -Wl,--no-undefined -Wl,-z,noexecstack -Wl,-z,relro -Wl,-z,now -Wl,--warn-shared-textrel -Wl,--fatal-warnings -u ANativeActivity_onCreate -L. -Lobj -Llib/armeabi-v8a -lraylib -lnative_app_glue -llog -landroid -lEGL -lGLESv2 -lOpenSLES -latomic -lc -lm -ldl

# Requires: obj/estadonovo.o
# Creates: lib/armeabi-v8a/libestadonovo.so

$ASDK/build-tools/28.0.1/aapt package -f -m -S res -J src -M AndroidManifest.xml -I $ASDK/platforms/android-22/android.jar

# Requires: AndroidManifest.xml, res/
# Creates: src/com/jardimdanificado/estadonovo/R.java

javac -verbose -source 1.7 -target 1.7 -d obj -bootclasspath /usr/lib/jvm/java-8-openjdk-amd64/jre/lib/jre/lib/rt.jar -classpath $ASDK/platforms/android-22/android.jar:obj -sourcepath src src/com/jardimdanificado/estadonovo/R.java src/com/jardimdanificado/estadonovo/NativeLoader.java

# Requires: src/com/jardimdanificado/estadonovo/R.java, src/com/jardimdanificado/estadonovo/NativeLoader.java
# Creates: obj/com/jardimdanificado/estadonovo/NativeLoader.class ... R&attr.class R$string.class R.class 

$ASDK/build-tools/28.0.1/dx --verbose --dex --output=dex/classes.dex obj 

# Requires: obj/com/jardimdanificado/estadonovo/NativeLoader.class ... R&attr.class R$string.class R.class 
# Creates: dex/classes.dex

$ASDK/build-tools/28.0.1/aapt package -f -M AndroidManifest.xml -S res -A assets -I $ASDK/platforms/android-22/android.jar -F estadonovo.unsigned.apk dex

# Creates: estadonovo.unsigned.apk
# Note: The "dex" at the end is the directory the classes.dex file is in! This folder can not contain the manifest file for whatever reason.

$ASDK/build-tools/28.0.1/aapt add estadonovo.unsigned.apk lib/armeabi-v8a/libestadonovo.so

# Does: Adds shared library to apk

jarsigner -keystore estadonovo.keystore -storepass whatever -keypass whatever -signedjar estadonovo.signed.apk estadonovo.unsigned.apk estadonovoKey

# Does: Signs

$ASDK/build-tools/28.0.1/zipalign -f 4 estadonovo.signed.apk estadonovo.apk

# Does: Aligns

$ASDK/platform-tools/adb install -r estadonovo.apk

# Does: install (on an Android phone that you connect with USB Debugging)s
EOF
chmod +x build.sh
