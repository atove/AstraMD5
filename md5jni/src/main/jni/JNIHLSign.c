#include <jni.h>
#include "md5.h"
#include <string.h>
#include <stdio.h>
#include "signaturecheck.h"
#include <android/log.h>

#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)

#define CBC 1
#define ECB 1

const char *UNSIGNATURE = "UNSIGNATURE";
//你的sign KEY
static const char MD5_KEY[] = "xxx";

JNIEXPORT jstring JNICALL
Java_com_astra_md5jni_SignTool_nSign(JNIEnv *env, jobject instance, jobject context, jstring str_) {

    //先进行apk被 二次打包的校验
    int hashCode = checkSignature(env, instance, context);
    //要把日志注掉
    LOGE("hashcode2: %d\n", hashCode);
    if (hashCode != -1 && hashCode != -2) {

        char* szText = (char*)(*env)->GetStringUTFChars(env, str_, JNI_FALSE);

        char buffer[2];
        //拼接的待加密字符串，可以根据自身需求修改
        sprintf(buffer, "%s%s%d", szText, MD5_KEY, hashCode);
        //要把日志注掉
        LOGD("待加密字符串: %s\n", buffer);

        MD5_CTX context = { 0 };
        MD5Init(&context);
        MD5Update(&context, buffer, strlen(buffer));
        uint8_t dest[16] = { 0 };
        MD5Final(dest, &context);
        (*env)->ReleaseStringUTFChars(env, str_, szText);

        int i = 0;
        char szMd5[32] = { 0 };
        for (i = 0; i < 16; i++)
        {
            sprintf(szMd5, "%s%02x", szMd5, dest[i]);
        }

        if (sizeof(int) == 4){

        } else{

        }


        sizeof(int) == 4, sizeof(long) == sizeof(long long) == 2 * sizeof(int);

        return (*env)->NewStringUTF(env, szMd5);

    } else{
        char *str = UNSIGNATURE;
        //此方法会乱码
        //return (*env)->NewString(env, str, strlen(str));
        return (*env)->NewStringUTF(env, str);
    }
}



jstring charToJstring(JNIEnv *envPtr, char *src) {
    JNIEnv env = *envPtr;

    jsize len = strlen(src);
    jclass clsstring = env->FindClass(envPtr, "java/lang/String");
    jstring strencode = env->NewStringUTF(envPtr, "UTF-8");
    jmethodID mid = env->GetMethodID(envPtr, clsstring, "<init>",
                                     "([BLjava/lang/String;)V");
    jbyteArray barr = env->NewByteArray(envPtr, len);
    env->SetByteArrayRegion(envPtr, barr, 0, len, (jbyte *) src);

    return (jstring) env->NewObject(envPtr, clsstring, mid, barr, strencode);
}


/**
 * if rerurn 1 ,is check pass.
 */
JNIEXPORT jint JNICALL
Java_com_androidyuan_aesjni_AESEncrypt_checkSignature(JNIEnv *env, jobject instance, jobject con) {

    return checkSignature(env, instance, con);
}

