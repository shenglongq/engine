// Copyright 2015 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef SHELL_PLATFORM_ANDROID_TEST_JNI_H_
#define SHELL_PLATFORM_ANDROID_TEST_JNI_H_

#include <string.h>
#include <jni.h>

#include "lib/fxl/macros.h"

namespace shell {

class NativeWx2DartBridge {
 public:
  ~NativeWx2DartBridge();

  static bool Register(JNIEnv* env);

 private:
  NativeWx2DartBridge();

  static jint CallNative(JNIEnv* env, jclass clazz,jstring instanceId,jstring tasks,jstring callback);

  static jint CallAddElement(JNIEnv* env, jclass clazz,jstring instanceId,jstring ref,jstring dom,jstring index,jstring callback);

  static void ReportJSException(JNIEnv* env, jclass clazz,jstring instanceId,jstring func,jstring exception);

  static void SetTimeoutNative(JNIEnv* env, jclass clazz,jstring callbackId,jstring time);

  static void SetJSFrmVersion(JNIEnv* env, jclass clazz,jstring version);

  static void NativeLog(JNIEnv* env, jclass clazz,jstring message);

  FXL_DISALLOW_COPY_AND_ASSIGN(NativeWx2DartBridge);
};

}  // namespace shell

#endif  // SHELL_PLATFORM_ANDROID_TEST_JNI_H_
