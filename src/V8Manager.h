#include "libplatform/libplatform.h"
#include "v8.h"
#include "util/Logger.h"

namespace NauLib {
  class V8Manager {
    private:
      v8::Isolate* v8Isolate;
      void load(v8::FunctionCallbackInfo<v8::Value>& args);
      void reportException(v8::TryCatch* tryCatch);
      Logger* logger;
    public:
      V8Manager(char **argv);
      void deconstruct();
  };
}
