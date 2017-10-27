// Copyright 2017 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef FLUTTER_SHELL_PLATFORM_IOS_EXTERNAL_TEXTURE_GL_H_
#define FLUTTER_SHELL_PLATFORM_IOS_EXTERNAL_TEXTURE_GL_H_

#import <CoreVideo/CoreVideo.h>
#import <OpenGLES/EAGL.h>
#import <OpenGLES/ES2/gl.h>
#import <OpenGLES/ES2/glext.h>
#include "flutter/flow/texture.h"
#include "flutter/fml/platform/darwin/cf_utils.h"
#include "flutter/fml/platform/darwin/scoped_nsobject.h"
#include "flutter/shell/platform/darwin/ios/framework/Headers/FlutterTexture.h"

namespace shell {

class IOSExternalTextureGL : public flow::Texture {
 public:
  IOSExternalTextureGL(int64_t textureId, NSObject<FlutterTexture>* externalTexture);

  ~IOSExternalTextureGL() override;

  // Called from GPU thread.
  virtual sk_sp<SkImage> MakeSkImage(int width,
                                     int height,
                                     GrContext* grContext) override;

  virtual void OnGrContextCreated() override;

  virtual void OnGrContextDestroyed() override;

 private:
  fml::scoped_nsobject<NSObject<FlutterTexture>> external_texture_;
  fml::CFRef<CVOpenGLESTextureCacheRef> cache_ref_;
  fml::CFRef<CVOpenGLESTextureRef> texture_ref_;
  FXL_DISALLOW_COPY_AND_ASSIGN(IOSExternalTextureGL);
};

}  // namespace shell

#endif  // FLUTTER_SHELL_PLATFORM_IOS_EXTERNAL_TEXTURE_GL_H_