// Copyright 2015 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef SHELL_PLATFORM_ANDROID_WEEX_WEEX_V8_H_
#define SHELL_PLATFORM_ANDROID_WEEX_WEEX_V8_H_

#include <string.h>
#include <jni.h>

#include "lib/fxl/macros.h"

#include "v8/include/v8.h"

#include "flutter/shell/platform/android/android_shell_holder.h"

namespace shell {

class WeexV8 {
 public:
  WeexV8(shell::AndroidShellHolder* shell_holder){
    this->shell_holder=shell_holder;
  }

  ~WeexV8(){
    delete(shell_holder);
  }

  jint initFramework(JNIEnv *env,jobject object, jstring script,jobject params);

 private:
  v8::Persistent<v8::Context> CreateShellContext();

  shell::AndroidShellHolder* shell_holder;

  bool ExecuteJavaScript(v8::Isolate *isolate,
                         v8::Handle<v8::String> source,
                         bool report_exceptions);

  void setJSFVersion(JNIEnv *env);

  void reportException(const char *instanceId, const char *func, const char *exception_string);

  void ReportException(v8::Isolate *isolate, v8::TryCatch *try_catch, const char *instanceId,
                       const char *func);

  FXL_DISALLOW_COPY_AND_ASSIGN(WeexV8);
};

}  // namespace shell

#endif  // SHELL_PLATFORM_ANDROID_TEST_JNI_H_