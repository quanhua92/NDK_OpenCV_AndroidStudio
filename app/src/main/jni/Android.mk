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