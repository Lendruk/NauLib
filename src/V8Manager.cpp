#include <stdio.h>
#include "libplatform/libplatform.h"
#include "v8.h"
#include "V8Manager.h"
#include <assert.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "util/FileService.h"

#include <cmrc/cmrc.hpp>

CMRC_DECLARE(js);

namespace NauLib {
  V8Manager::V8Manager(char **argv) {
    this->logger = new Logger();
    // Initialize V8.
    v8::V8::InitializeICUDefaultLocation(argv[0]);
    v8::V8::InitializeExternalStartupData(argv[0]);
    std::unique_ptr<v8::Platform> platform = v8::platform::NewDefaultPlatform();
    v8::V8::InitializePlatform(platform.get());
    v8::V8::Initialize();

    // Create a new Isolate and make it the current one.
    v8::Isolate::CreateParams create_params;
    create_params.array_buffer_allocator =
        v8::ArrayBuffer::Allocator::NewDefaultAllocator();
        
    v8Isolate = v8::Isolate::New(create_params);
    {
        v8::Isolate::Scope isolzate_scope(v8Isolate);

        // Create a stack-allocated handle scope.
        v8::HandleScope handle_scope(v8Isolate);

        // Create a new context.
        v8::Local<v8::Context> context = v8::Context::New(v8Isolate);

        // Enter the context for compiling and running the hello world script.
        v8::Context::Scope context_scope(context);

        // Create a string containing the JavaScript source code.

        auto fs = cmrc::js::get_filesystem();
        auto data = fs.open("test.js");
        
        string test = std::string(data.begin(), data.end());

        cout << test << "\n";
        cout << "prints file" << "\n";
        char* testArr = new char[test.length()+1];
        testArr[test.length()] = '\0';
        test.copy(testArr, test.size() + 1);
        v8::MaybeLocal<v8::String> maybeSource = v8::String::NewFromUtf8(
        v8Isolate, testArr, v8::NewStringType::kNormal, static_cast<int>(test.length()));
            // v8::String::NewFromUtf8Literal(v8Isolate, "'Hello' + ', World!'");
        v8::Local<v8::String> source;
        maybeSource.ToLocal(&source);
        v8::Local<v8::Value> name;
        // Compile the source code.
        v8::Local<v8::Script> script;
        v8::ScriptOrigin origin(v8Isolate, name);
        
        v8::TryCatch tryCatch(this->v8Isolate);
        if(!v8::Script::Compile(context, source, &origin).ToLocal(&script)) {
          this->reportException(&tryCatch);
        } else {
          // Run the script to get the result.
          v8::Local<v8::Value> result = script->Run(context).ToLocalChecked();

          // Convert the result to an UTF8 string and print it.
          v8::String::Utf8Value utf8(v8Isolate, result);
          printf("result -> %s\n", *utf8);  
        }

        delete create_params.array_buffer_allocator;
    }
  }


  void V8Manager::deconstruct() {
    // Dispose the isolate and tear down V8.
    v8Isolate->Dispose();
    v8::V8::Dispose();
    v8::V8::ShutdownPlatform();
  }

  
  // Extracts a C string from a V8 Utf8Value.
  const char* ToCString(const v8::String::Utf8Value& value) {
    return *value ? *value : "<string conversion failed>";
  }

  void V8Manager::reportException(v8::TryCatch* try_catch) {
      v8::HandleScope handle_scope(this->v8Isolate);
      v8::String::Utf8Value exception(this->v8Isolate, try_catch->Exception());
      const char* exception_string = ToCString(exception);
      v8::Local<v8::Message> message = try_catch->Message();
      if (message.IsEmpty()) {
        // V8 didn't provide any extra information about this error; just
        // print the exception.
        fprintf(stderr, "%s\n", exception_string);
      } else {
        // Print (filename):(line number): (message).
        v8::String::Utf8Value filename(this->v8Isolate,
                                       message->GetScriptOrigin().ResourceName());
        v8::Local<v8::Context> context(this->v8Isolate->GetCurrentContext());
        const char* filename_string = ToCString(filename);
        int linenum = message->GetLineNumber(context).FromJust();
        fprintf(stderr, "%s:%i: %s\n", filename_string, linenum, exception_string);
        // Print line of source code.
        v8::String::Utf8Value sourceline(
            this->v8Isolate, message->GetSourceLine(context).ToLocalChecked());
        const char* sourceline_string = ToCString(sourceline);
        fprintf(stderr, "%s\n", sourceline_string);
        // Print wavy underline (GetUnderline is deprecated).
        int start = message->GetStartColumn(context).FromJust();
        for (int i = 0; i < start; i++) {
          fprintf(stderr, " ");
        }
        int end = message->GetEndColumn(context).FromJust();
        for (int i = start; i < end; i++) {
          fprintf(stderr, "^");
        }
        fprintf(stderr, "\n");
        v8::Local<v8::Value> stack_trace_string;
        if (try_catch->StackTrace(context).ToLocal(&stack_trace_string) &&
            stack_trace_string->IsString() &&
            stack_trace_string.As<v8::String>()->Length() > 0) {
          v8::String::Utf8Value stack_trace(this->v8Isolate, stack_trace_string);
          const char* stack_trace_string = ToCString(stack_trace);
          fprintf(stderr, "%s\n", stack_trace_string);
      }
    }
  }

}