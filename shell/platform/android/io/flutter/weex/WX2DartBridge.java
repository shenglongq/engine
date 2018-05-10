package com.beanfactory.doumi;

/**
 * Created by alvin on 08/05/2018.
 */

public class WX2DartBridge {
    private static WX2DartBridge instance;

    public static WX2DartBridge getInstance(){
        if(instance==null){
            instance=new WX2DartBridge();
        }
        return instance;
    }

    private WX2DartBridge(){

    }

    public native void init(String script, WXParams params);

    public int callNative(String instanceId, String tasks, String callback) {
        return NativeWx2DartBridge.callNative(instanceId,tasks,callback);
    }

    public int callAddElement(String instanceId, String ref,String dom,String index, String callback) {
        return NativeWx2DartBridge.callAddElement(instanceId,ref,dom,index,callback);
    }

    public void reportJSException(String instanceId, String func, String exception) {
        NativeWx2DartBridge.reportJSException(instanceId,func,exception);
    }


    public void setTimeoutNative(String callbackId, String time) {
        NativeWx2DartBridge.setTimeoutNative(callbackId,time);
    }

    public void setJSFrmVersion(String version) {
        NativeWx2DartBridge.setJSFrmVersion(version);
    }

    public void nativeLog(String message){
        NativeWx2DartBridge.nativeLog(message);
    }
}
