#include <com_example_ndk_opencv_androidstudio_NativeClass.h>

JNIEXPORT jstring JNICALL Java_com_example_ndk_1opencv_1androidstudio_NativeClass_getStringFromNative
  (JNIEnv * env, jobject obj){
    return env->NewStringUTF("Hello from JNI");
}