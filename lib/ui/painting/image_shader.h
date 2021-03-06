// Copyright 2015 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef FLUTTER_LIB_UI_PAINTING_IMAGE_SHADER_H_
#define FLUTTER_LIB_UI_PAINTING_IMAGE_SHADER_H_

#include "flutter/lib/ui/painting/gradient.h"
#include "flutter/lib/ui/painting/image.h"
#include "flutter/lib/ui/painting/matrix.h"
#include "flutter/lib/ui/painting/shader.h"
#include "lib/tonic/dart_wrappable.h"
#include "lib/tonic/typed_data/float64_list.h"
#include "third_party/skia/include/core/SkMatrix.h"
#include "third_party/skia/include/core/SkShader.h"

namespace tonic {
class DartLibraryNatives;
}  // namespace tonic

namespace blink {

class ImageShader : public Shader {
  DEFINE_WRAPPERTYPEINFO();
  FRIEND_MAKE_REF_COUNTED(ImageShader);

 public:
  ~ImageShader() override;
  static fxl::RefPtr<ImageShader> Create();

  void initWithImage(CanvasImage* image,
                     SkShader::TileMode tmx,
                     SkShader::TileMode tmy,
                     const tonic::Float64List& matrix4);

  static void RegisterNatives(tonic::DartLibraryNatives* natives);

 private:
  ImageShader();
};

}  // namespace blink

#endif  // FLUTTER_LIB_UI_PAINTING_IMAGE_SHADER_H_
