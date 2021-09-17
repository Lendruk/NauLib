#include "libplatform/libplatform.h"
#include "v8.h"
#include <stdlib.h>
#include <string.h>
#include "GlobalMapper.h"
#include "util/FileService.h"

namespace NauLib {
  void readFileCallback(const v8::FunctionCallbackInfo<v8::Value>& args) {
    if (args.Length() < 1) return;
    v8::Isolate* isolate = args.GetIsolate();
    v8::HandleScope scope(isolate);
    v8::Local<v8::Value> arg = args[0];
    v8::String::Utf8Value value(isolate, arg);
    NauLib::readFile(*value);
  }


  v8::Local<v8::ObjectTemplate> mapGlobals(v8::Isolate* v8Isolate) {
    //Register global APIs
    v8::Local<v8::ObjectTemplate> globalTemplate = v8::ObjectTemplate::New(v8Isolate);
    globalTemplate->Set(v8Isolate, "fs", v8::FunctionTemplate::New(v8Isolate, readFileCallback));
    return globalTemplate;
  }
}