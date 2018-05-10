#include "flutter/shell/platform/android/native_wx_2_dart_bridge.h"

#include "lib/fxl/arraysize.h"
#include "lib/fxl/logging.h"
#include "lib/fxl/strings/string_printf.h"

#include "flutter/lib/ui/ui_dart_state.h"
#include "flutter/shell/platform/android/android_shell_holder.h"

#include <android/log.h>

namespace shell {

NativeWx2DartBridge::NativeWx2DartBridge(){}

NativeWx2DartBridge::~NativeWx2DartBridge() = default;

bool NativeWx2DartBridge::Register(JNIEnv* env) {
  static const JNINativeMethod methods[] = {
      {
          .name = "callNative",
          .signature = "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)I",
          .fnPtr = reinterpret_cast<void*>(&CallNative),
      },
      {
          .name = "callAddElement",
          .signature = "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)I",
          .fnPtr = reinterpret_cast<void*>(&CallAddElement),
      },
      {
          .name = "reportJSException",
          .signature = "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)V",
          .fnPtr = reinterpret_cast<void*>(&ReportJSException),
      },
      {
          .name = "setTimeoutNative",
          .signature = "(Ljava/lang/String;Ljava/lang/String;)V",
          .fnPtr = reinterpret_cast<void*>(&SetTimeoutNative),
      },
      {
          .name = "setJSFrmVersion",
          .signature = "(Ljava/lang/String;)V",
          .fnPtr = reinterpret_cast<void*>(&SetJSFrmVersion),
      },
      {
          .name = "nativeLog",
          .signature = "(Ljava/lang/String;)V",
          .fnPtr = reinterpret_cast<void*>(&NativeLog),
      },
  };

  jclass clazz = env->FindClass("com/beanfactory/doumi/NativeWx2DartBridge");

  if (clazz == nullptr) {
    return false;
  }

  return env->RegisterNatives(clazz, methods, arraysize(methods)) == 0;
}

char* jstringToChar(JNIEnv* env, jstring jstr) {
    char* rtn = NULL;
    jclass clsstring = env->FindClass("java/lang/String");
    jstring strencode = env->NewStringUTF("GB2312");
    jmethodID mid = env->GetMethodID(clsstring, "getBytes", "(Ljava/lang/String;)[B");
    jbyteArray barr = (jbyteArray) env->CallObjectMethod(jstr, mid, strencode);
    jsize alen = env->GetArrayLength(barr);
    jbyte* ba = env->GetByteArrayElements(barr, JNI_FALSE);
    if (alen > 0) {
        rtn = (char*) malloc(alen + 1);
        memcpy(rtn, ba, alen);
        rtn[alen] = 0;
    }
    env->ReleaseByteArrayElements(barr, ba, 0);
    return rtn;
}

jint NativeWx2DartBridge::CallNative(JNIEnv* env, jclass clazz,jstring instanceId,jstring tasks,jstring callback){
    //blink::UIDartState::Current()->window()->CallNative(jstringToChar(env,instanceId),jstringToChar(env,tasks),jstringToChar(env,callback));
    return 1;
}

jint NativeWx2DartBridge::CallAddElement(JNIEnv* env, jclass clazz,jstring instanceId,jstring ref,jstring dom,jstring index,jstring callback){
    //blink::UIDartState::Current()->window()->CallAddElement(jstringToChar(env,instanceId),jstringToChar(env,ref),jstringToChar(env,dom),jstringToChar(env,index),jstringToChar(env,callback));
    return 1;
}

void NativeWx2DartBridge::ReportJSException(JNIEnv* env, jclass clazz,jstring instanceId,jstring func,jstring exception){
    //blink::UIDartState::Current()->window()->ReportException(jstringToChar(env,instanceId),jstringToChar(env,func),jstringToChar(env,exception));
}

void NativeWx2DartBridge::SetTimeoutNative(JNIEnv* env, jclass clazz,jstring callbackId,jstring time){
    //blink::UIDartState::Current()->window()->SetTimeoutNative(jstringToChar(env,callbackId),jstringToChar(env,time));
}

void NativeWx2DartBridge::SetJSFrmVersion(JNIEnv* env, jclass clazz,jstring version){
    //blink::UIDartState::Current()->window()->SetJSFrmVersion(jstringToChar(env,version));
}

void NativeWx2DartBridge::NativeLog(JNIEnv* env, jclass clazz,jstring message){
    //blink::UIDartState::Current()->window()->NativeLog(jstringToChar(env,message));
}

}  // namespace shell
