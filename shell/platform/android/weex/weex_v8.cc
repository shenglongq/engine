#include "flutter/shell/platform/android/weex/weex_v8.h"

#include "lib/fxl/arraysize.h"
#include "lib/fxl/logging.h"
#include "lib/fxl/strings/string_printf.h"

#include "flutter/lib/ui/ui_dart_state.h"

#include <android/log.h>
#include <assert.h>
#include <fcntl.h>

#define LOG_TAG "WEEX_V8"
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG ,__VA_ARGS__) // 定义LOGD类型
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO,LOG_TAG ,__VA_ARGS__) // 定义LOGI类型
#define LOGW(...) __android_log_print(ANDROID_LOG_WARN,LOG_TAG ,__VA_ARGS__) // 定义LOGW类型
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR,LOG_TAG ,__VA_ARGS__) // 定义LOGE类型
#define LOGF(...) __android_log_print(ANDROID_LOG_FATAL,LOG_TAG ,__VA_ARGS__) // 定义LOGF类型

namespace shell {

v8::Handle<v8::Value> callNative(const v8::Arguments &args);

v8::Handle<v8::Value> callAddElement(const v8::Arguments &args);

v8::Handle<v8::Value> setTimeoutNative(const v8::Arguments &args);

v8::Handle<v8::Value> nativeLog(const v8::Arguments &args);

v8::Persistent<v8::Context> V8context;
v8::Isolate *globalIsolate;
v8::Handle<v8::Object> json;
v8::Handle<v8::Function> json_parse;
v8::Handle<v8::Function> json_stringify;

v8::Handle<v8::ObjectTemplate> WXEnvironment;

const char *ToCString(const v8::String::Utf8Value &value) {
    return *value ? *value : "<string conversion failed>";
}

jint WeexV8::initFramework(JNIEnv *env,jobject object, jstring script,jobject params){
    // no flush to avoid SIGILL
    // const char* str= "--noflush_code_incrementally --noflush_code --noage_code";
    const char *str = "--noflush_code --noage_code --nocompact_code_space"
            " --expose_gc";
    v8::V8::SetFlagsFromString(str, strlen(str));

    v8::V8::Initialize();
    globalIsolate = v8::Isolate::GetCurrent();

    v8::HandleScope handleScope;

    WXEnvironment = v8::ObjectTemplate::New();

    /*jclass c_params = env->GetObjectClass(params);

    jmethodID m_platform = env->GetMethodID(c_params, "getPlatform", "()Ljava/lang/String;");
    jobject platform = env->CallObjectMethod(params, m_platform);
    WXEnvironment->Set("platform", jString2V8String(env, (jstring) platform));
    env->DeleteLocalRef(platform);

    jmethodID m_osVersion = env->GetMethodID(c_params, "getOsVersion", "()Ljava/lang/String;");
    jobject osVersion = env->CallObjectMethod(params, m_osVersion);
    WXEnvironment->Set("osVersion", jString2V8String(env, (jstring) osVersion));
    env->DeleteLocalRef(osVersion);

    jmethodID m_appVersion = env->GetMethodID(c_params, "getAppVersion", "()Ljava/lang/String;");
    jobject appVersion = env->CallObjectMethod(params, m_appVersion);
    WXEnvironment->Set("appVersion", jString2V8String(env, (jstring) appVersion));
    env->DeleteLocalRef(appVersion);

    jmethodID m_weexVersion = env->GetMethodID(c_params, "getWeexVersion", "()Ljava/lang/String;");
    jobject weexVersion = env->CallObjectMethod(params, m_weexVersion);
    WXEnvironment->Set("weexVersion", jString2V8String(env, (jstring) weexVersion));
    env->DeleteLocalRef(weexVersion);

    jmethodID m_deviceModel = env->GetMethodID(c_params, "getDeviceModel", "()Ljava/lang/String;");
    jobject deviceModel = env->CallObjectMethod(params, m_deviceModel);
    WXEnvironment->Set("deviceModel", jString2V8String(env, (jstring) deviceModel));
    env->DeleteLocalRef(deviceModel);

    jmethodID m_appName = env->GetMethodID(c_params, "getAppName", "()Ljava/lang/String;");
    jobject appName = env->CallObjectMethod(params, m_appName);
    WXEnvironment->Set("appName", jString2V8String(env, (jstring) appName));
    env->DeleteLocalRef(appName);

    jmethodID m_deviceWidth = env->GetMethodID(c_params, "getDeviceWidth", "()Ljava/lang/String;");
    jobject deviceWidth = env->CallObjectMethod(params, m_deviceWidth);
    WXEnvironment->Set("deviceWidth", jString2V8String(env, (jstring) deviceWidth));
    env->DeleteLocalRef(deviceWidth);

    jmethodID m_deviceHeight = env->GetMethodID(c_params, "getDeviceHeight",
                                                "()Ljava/lang/String;");
    jobject deviceHeight = env->CallObjectMethod(params, m_deviceHeight);
    WXEnvironment->Set("deviceHeight", jString2V8String(env, (jstring) deviceHeight));
    env->DeleteLocalRef(deviceHeight);

    jmethodID m_options = env->GetMethodID(c_params, "getOptions", "()Ljava/lang/Object;");
    jobject options = env->CallObjectMethod(params, m_options);
    jclass jmapclass = env->FindClass("java/util/HashMap");
    jmethodID jkeysetmid = env->GetMethodID(jmapclass, "keySet", "()Ljava/util/Set;");
    jmethodID jgetmid = env->GetMethodID(jmapclass, "get", "(Ljava/lang/Object;)Ljava/lang/Object;");
    jobject jsetkey = env->CallObjectMethod(options, jkeysetmid);
    jclass jsetclass = env->FindClass("java/util/Set");
    jmethodID jtoArraymid = env->GetMethodID(jsetclass, "toArray", "()[Ljava/lang/Object;");
    jobjectArray jobjArray = (jobjectArray)env->CallObjectMethod(jsetkey, jtoArraymid);
    env->DeleteLocalRef(jsetkey);
    if (jobjArray != NULL) {
        jsize arraysize = env->GetArrayLength(jobjArray);
        for(int i = 0; i < arraysize; i++) {
            jstring jkey = (jstring)env->GetObjectArrayElement(jobjArray, i);
            jstring jvalue = (jstring)env->CallObjectMethod(options, jgetmid, jkey);
            const char *c_key = env->GetStringUTFChars(jkey, NULL);
            const char *c_value = env->GetStringUTFChars(jvalue, NULL);
            LOGI("options array k:%s v:%s", c_key, c_value);
            WXEnvironment->Set(c_key, jString2V8String(env, jvalue));
            env->DeleteLocalRef(jkey);
            env->DeleteLocalRef(jvalue);
        }
        env->DeleteLocalRef(jobjArray);
    }
    env->DeleteLocalRef(options);*/

    V8context = CreateShellContext();

    const char *scriptStr = env->GetStringUTFChars(script, NULL);
    if (scriptStr == NULL || !ExecuteJavaScript(globalIsolate, v8::String::New(scriptStr), true)) {
        return false;
    }

    setJSFVersion(env);
    env->ReleaseStringUTFChars(script, scriptStr);
    //env->DeleteLocalRef(c_params);

    return true;
}

v8::Persistent<v8::Context> WeexV8::CreateShellContext() {

    // Create a template for the global object.
    v8::Handle<v8::ObjectTemplate> global = v8::ObjectTemplate::New();

    // Bind the global 'callNative' function to the C++  callNative.
    global->Set(v8::String::New("callNative"), v8::FunctionTemplate::New(callNative));

    // Bind the global 'callAddElement' function to the C++  callNative.
    global->Set(v8::String::New("callAddElement"), v8::FunctionTemplate::New(callAddElement));

    // Bind the global 'setTimeoutNative' function to the C++ setTimeoutNative.
    global->Set(v8::String::New("setTimeoutNative"), v8::FunctionTemplate::New(setTimeoutNative));

    // Bind the global 'nativeLog' function to the C++ Print callback.
    global->Set(v8::String::New("nativeLog"), v8::FunctionTemplate::New(nativeLog));

    // Bind the global 'WXEnvironment' Object.
    global->Set(v8::String::New("WXEnvironment"), WXEnvironment);

    return v8::Context::New(NULL, global);
}

/**
 * this function is to execute a section of JavaScript content.
 */
bool WeexV8::ExecuteJavaScript(v8::Isolate *isolate,
                       v8::Handle<v8::String> source,
                       bool report_exceptions) {
    v8::Isolate::Scope isolate_scope(isolate);
    v8::Context::Scope ctx_scope(V8context);
    v8::TryCatch try_catch;
    if (source.IsEmpty()) {
        if (report_exceptions)
            ReportException(isolate, &try_catch, NULL, "");
        return false;
    }
    v8::Handle<v8::String> name = v8::String::New("(weex)");
    v8::Handle<v8::Script> script = v8::Script::Compile(source, name);
    if (script.IsEmpty()) {
        if (report_exceptions)
            ReportException(isolate, &try_catch, NULL, "");
        return false;
    } else {
        v8::Handle<v8::Value> result = script->Run();
        if (result.IsEmpty()) {
            assert(try_catch.HasCaught());
            if (report_exceptions)
                ReportException(isolate, &try_catch, NULL, "");
            return false;
        } else {
            assert(!try_catch.HasCaught());
            return true;
        }
    }
}

void WeexV8::setJSFVersion(JNIEnv *env) {

    v8::HandleScope handleScope;
    v8::Isolate::Scope isolate_scope(globalIsolate);
    v8::Context::Scope ctx_scope(V8context);
    // v8::TryCatch try_catch;

    v8::Handle<v8::Object> global = V8context->Global();
    v8::Handle<v8::Function> getJSFMVersion;
    v8::Handle<v8::Value> version;
    getJSFMVersion = v8::Handle<v8::Function>::Cast(global->Get(v8::String::New("getJSFMVersion")));
    version = getJSFMVersion->Call(global, 0, NULL);
    v8::String::Utf8Value str(version);

    blink::UIDartState::Current()->window()->SetJSFrmVersion(ToCString(str));
}

void WeexV8::reportException(const char *instanceId, const char *func, const char *exception_string) {
    blink::UIDartState::Current()->window()->ReportException(instanceId,func,exception_string);
}

void WeexV8::ReportException(v8::Isolate *isolate, v8::TryCatch *try_catch, const char *instanceId,
                     const char *func) {
    v8::HandleScope handle_scope(isolate);
    v8::String::Utf8Value exception(try_catch->Exception());
    v8::Handle<v8::Message> message = try_catch->Message();
    if (message.IsEmpty()) {
        LOGE(" ReportException : %s", ToCString(exception));
    } else {
        v8::String::Utf8Value filename(message->GetScriptResourceName());
        const char *filename_string = ToCString(filename);
        int lineNum = message->GetLineNumber();
        LOGE(" ReportException :%s:%i: %s", filename_string, lineNum, ToCString(exception));
        // Print line of source code.
        v8::String::Utf8Value stack_trace(try_catch->StackTrace());
        if (stack_trace.length() > 0) {
            const char *stack_trace_string = ToCString(stack_trace);
            LOGE(" ReportException : %s", stack_trace_string);
        }
    }
    reportException(instanceId, func, ToCString(exception));
}

/**
 *  This Function is a built-in function that JS bundle can execute
 *  to call native module.
 */
v8::Handle<v8::Value> callNative(const v8::Arguments &args) {
    //instacneID args[0]
    const char* jInstanceId = NULL;
    if (!args[0].IsEmpty()) {
        v8::String::Utf8Value instanceId(args[0]);
        jInstanceId = ToCString(instanceId);
    }
    //task args[1]
    const char* jTaskString = NULL;
    if (!args[1].IsEmpty() && args[1]->IsObject()) {
        v8::Handle<v8::Value> obj[1];
        v8::Handle<v8::Object> global = V8context->Global();
        json = v8::Handle<v8::Object>::Cast(global->Get(v8::String::New("JSON")));
        json_stringify = v8::Handle<v8::Function>::Cast(json->Get(v8::String::New("stringify")));
        obj[0] = args[1];
        v8::Handle<v8::Value> ret = json_stringify->Call(json, 1, obj);
        v8::String::Utf8Value str(ret);

        jTaskString=ToCString(str);
    } else if (!args[1].IsEmpty() && args[1]->IsString()) {
        v8::String::Utf8Value tasks(args[1]);

        jTaskString=ToCString(tasks);
    }
    //callback args[2]
    const char* jcallback = NULL;
    if (!args[2].IsEmpty()) {
        v8::String::Utf8Value callback(args[2]);
        jcallback=ToCString(callback);
    }

    blink::UIDartState::Current()->window()->CallNative(jInstanceId,jTaskString,jcallback);

    return v8::Integer::New(1);
}

v8::Handle<v8::Value> callAddElement(const v8::Arguments &args) {
    //instacneID args[0]
    const char* jInstanceId = NULL;
    if (!args[0].IsEmpty()) {
        v8::String::Utf8Value instanceId(args[0]);
        jInstanceId = ToCString(instanceId);
    }
    //instacneID args[1]
    const char* jref = NULL;
    if (!args[1].IsEmpty()) {
        v8::String::Utf8Value ref(args[1]);
        jref = ToCString(ref);
    }
    //dom node args[2]
    const char* jdomString = NULL;
    if (!args[2].IsEmpty() && args[2]->IsObject()) {

        v8::Handle<v8::Value> obj[1];
        v8::Handle<v8::Object> global = V8context->Global();
        json = v8::Handle<v8::Object>::Cast(global->Get(v8::String::New("JSON")));
        json_stringify = v8::Handle<v8::Function>::Cast(json->Get(v8::String::New("stringify")));
        obj[0] = args[2];
        v8::Handle<v8::Value> ret = json_stringify->Call(json, 1, obj);
        v8::String::Utf8Value str(ret);

        jdomString = ToCString(str);
    } else if (args[2].IsEmpty() && args[2]->IsString()) {
        v8::String::Utf8Value tasks(args[2]);

        jdomString = ToCString(tasks);
    }

    //index  args[3]
    const char* jindex = NULL;
    if (!args[3].IsEmpty()) {
        v8::String::Utf8Value index(args[3]);
        jindex=ToCString(index);
    }
    //callback  args[4]
    const char* jCallback = NULL;
    if (!args[4].IsEmpty()) {
        v8::String::Utf8Value callback(args[4]);
        jCallback=ToCString(callback);
    }

    blink::UIDartState::Current()->window()->CallAddElement(jInstanceId,jref,jdomString,jindex,jCallback);

    return v8::Integer::New(1);
}

v8::Handle<v8::Value> setTimeoutNative(const v8::Arguments &args) {
    //callbackId
    v8::String::Utf8Value callbackID(args[0]);

    //time
    v8::String::Utf8Value time(args[1]);

    blink::UIDartState::Current()->window()->SetTimeoutNative(ToCString(callbackID),ToCString(time));
    return v8::Boolean::New(true);
}

v8::Handle<v8::Value> nativeLog(const v8::Arguments &args) {
    v8::Handle<v8::String> accumulator = v8::String::Empty();
    for (int i = 0; i < args.Length(); i++) {
        v8::Local<v8::String> str_arg = args[i]->ToString();
        if (!str_arg.IsEmpty()) {
            accumulator = v8::String::Concat(accumulator, str_arg);
        }
    }
    if (!accumulator.IsEmpty()) {
        v8::String::Utf8Value arg(accumulator);

        blink::UIDartState::Current()->window()->NativeLog("jsLog",ToCString(arg));
    }

    return v8::Boolean::New(1);
}

}  // namespace shell
