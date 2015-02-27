Step to use NDK in Android Studio:
==============

1. Create class NativeClass with function getStringFromNative:

<pre>
public class NativeClass {
    public native String getStringFromNative();
}
</pre>

2. Build project to generate classes

3. Open terminal. Change to app/src/main. Then run

<pre>
javah -d jni -classpath ../../build/intermediates/classes/debug/ com.example.ndk_opencv_androidstudio.NativeClass
</pre>

4. Add NDK Directory to local.properties file (not on github)

<pre>
ndk.dir=/home/robotbase/Android/NDK64/android-ndk-r10d
</pre>

5. Create "com_example_ndk_opencv_androidstudio_NativeClass.cpp" in c folder (jni folder).

<pre>
#include <com_example_ndk_opencv_androidstudio_NativeClass.h>

JNIEXPORT jstring JNICALL Java_com_example_ndk_1opencv_1androidstudio_NativeClass_getStringFromNative
  (JNIEnv * env, jobject obj){
    return env->NewStringUTF("Hello from JNI");
}
</pre>

6. Edit build.gradle. Add ndk moduleName in  defaultConfig 

<pre>
defaultConfig {
        applicationId "com.example.ndk_opencv_androidstudio"
        minSdkVersion 15
        targetSdkVersion 21
        versionCode 1
        versionName "1.0"

        ndk {
            moduleName "MyLib"
        }
    }
</pre>

7. Load MyLib in MainActivity

<pre>
    static {
        System.loadLibrary("MyLib");
    }
</pre>

8. Add id to TextView

<pre>
android:id="@+id/testTextView"
</pre>

9. Use getStringFromNative() to change testTextView text

<pre>
    TextView tv = (TextView) findViewById(R.id.testTextView);
    tv.setText(NativeClass.getStringFromNative());
</pre>


Step to use OpenCV:
==============

Reference:
==============
1. http://hujiaweibujidao.github.io/blog/2014/10/22/android-ndk-and-opencv-development-with-android-studio/