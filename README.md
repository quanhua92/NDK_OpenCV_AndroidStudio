Step to use NDK in Android Studio:
==============

- Create class NativeClass with function getStringFromNative:

<pre>
public class NativeClass {
    public native static String getStringFromNative();
}
</pre>

- Build project to generate classes

- Open terminal. Change to app/src/main. Then run

<pre>
javah -d jni -classpath ../../build/intermediates/classes/debug/ com.example.ndk_opencv_androidstudio.NativeClass
</pre>

- Create "com_example_ndk_opencv_androidstudio_NativeClass.cpp" in c folder (jni folder).

<pre>
#include <com_example_ndk_opencv_androidstudio_NativeClass.h>

JNIEXPORT jstring JNICALL Java_com_example_ndk_1opencv_1androidstudio_NativeClass_getStringFromNative
  (JNIEnv * env, jobject obj){
    return env->NewStringUTF("Hello from JNI");
}
</pre>

- Edit build.gradle. Add ndk moduleName in  defaultConfig 

<pre>
defaultConfig {
        applicationId "com.example.ndk_opencv_androidstudio"
        minSdkVersion 15
        targetSdkVersion 21
        versionCode 1
        versionName "-0"

        ndk {
            moduleName "MyLib"
        }
    }
</pre>

- Load MyLib in MainActivity

<pre>
    static {
        System.loadLibrary("MyLib");
    }
</pre>

- Add id to TextView

<pre>
android:id="@+id/testTextView"
</pre>

- Use getStringFromNative() to change testTextView text

<pre>
    TextView tv = (TextView) findViewById(R.id.testTextView);
    tv.setText(NativeClass.getStringFromNative());
</pre>


Step to use OpenCV:
==============

- Open build.gradle. Add this before buildTypes

<pre>
    // begin
    sourceSets.main {
        jni.srcDirs = [] //disable automatic ndk-build call
    }
    task ndkBuild(type: Exec, description: 'Compile JNI source via NDK') {
        commandLine "/home/robotbase/Android/NDK64/android-ndk-r10d/ndk-build",
                'NDK_PROJECT_PATH=build/intermediates/ndk',
                'NDK_LIBS_OUT=src/main/jniLibs',
                'APP_BUILD_SCRIPT=src/main/jni/Android.mk',
                'NDK_APPLICATION_MK=src/main/jni/Application.mk'
    }
    tasks.withType(JavaCompile) {
        compileTask -> compileTask.dependsOn ndkBuild
    }
    //end
</pre>

- Android.mk

<pre>
LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_SRC_FILES := com_example_ndk_opencv_androidstudio_NativeClass.cpp
LOCAL_LDLIBS += -llog
LOCAL_MODULE := MyLib

include $(BUILD_SHARED_LIBRARY)
</pre>
- Application.mk

<pre>
APP_STL := gnustl_static
APP_CPPFLAGS := -frtti -fexceptions
APP_ABI := armeabi-v7a
APP_PLATFORM := android-16
</pre>

- Download OpenCV: http://sourceforge.net/projects/opencvlibrary/files/opencv-android/

- Edit Android.mk

<pre>
LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

#opencv
OPENCVROOT:= /home/robotbase/Android/OpenCV-2.4.10-android-sdk
OPENCV_CAMERA_MODULES:=on
OPENCV_INSTALL_MODULES:=on
OPENCV_LIB_TYPE:=SHARED
include ${OPENCVROOT}/sdk/native/jni/OpenCV.mk


LOCAL_SRC_FILES := com_example_ndk_opencv_androidstudio_NativeClass.cpp
LOCAL_LDLIBS += -llog
LOCAL_MODULE := MyLib

include $(BUILD_SHARED_LIBRARY)
</pre>

- Edit MainActivity.java

<pre>
static {
    System.loadLibrary("MyLib");
    System.loadLibrary("opencv_java");
}
</pre>
Step to use OpenCV in Java:
==============

- Open Android Studio, choose import 
- Select OpenCV-2.4.10-android-sdk/sdk/java/ -> choose new location ** opencv-java **
- Build > Rebuild Project
- Close Project
- Open NDK_OpenCV_AndroidStudio
- File > Import Module
- Select ** opencv-java **
- Edit build.gradle

<pre>
dependencies {
	...
    compile project(':opencv-java')
}
- Import org.opencv.... and code OpenCv in Java
</pre>

Reference:
==============
- http://hujiaweibujidao.github.io/blog/2014/10/22/android-ndk-and-opencv-development-with-android-studio/
- http://answers.opencv.org/question/14546/how-to-work-with-opencv4android-in-android-studio/