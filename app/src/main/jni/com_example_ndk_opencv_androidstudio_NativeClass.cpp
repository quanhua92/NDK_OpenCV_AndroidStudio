#include <com_example_ndk_opencv_androidstudio_NativeClass.h>
#include "opencv2/opencv.hpp"
#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
using namespace std;
using namespace cv;

JNIEXPORT jstring JNICALL Java_com_example_ndk_1opencv_1androidstudio_NativeClass_getStringFromNative
  (JNIEnv * env, jobject obj){
    return env->NewStringUTF("Hello from JNI");
}