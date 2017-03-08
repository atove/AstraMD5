LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := CTestMD5
LOCAL_SRC_FILES := test_md5.c md5.c
LOCAL_LDLIBS += -llog -ldl

include $(BUILD_SHARED_LIBRARY)