package com.beanfactory.doumi;

/**
 * Created by alvin on 08/05/2018.
 */

public class NativeWx2DartBridge {

    public static native int callNative(String instanceId, String tasks, String callback);

    public static native int callAddElement(String instanceId, String ref,String dom,String index, String callback);

    public static native void reportJSException(String instanceId, String func, String exception);
    
    public static native void setTimeoutNative(String callbackId, String time);

    public static native void setJSFrmVersion(String version);

    public static native void nativeLog(String message);

}
