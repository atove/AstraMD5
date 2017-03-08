package com.astra.md5jni;

import android.content.Context;
import android.util.Log;

/**
 * Created by Astra on 17/1/6.
 */

public class SignTool {
    static {
        System.loadLibrary("JNIHLSign");
        /*try{
            System.loadLibrary("JNIHLSign");
        }catch (UnsatisfiedLinkError e){
            Log.e("md5jni加载失败", e.toString());
        }*/
    }

    public static String sign(Context context, String str){
        try {
            return nSign(context, str);
        }catch (UnsatisfiedLinkError e){
            Log.d("md5jni签名失败", e.toString());
            return "sign error";
        }
    }

    private static native String nSign(Context context, String str);
}
