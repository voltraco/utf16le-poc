#include <v8.h>
#include <assert.h>
#include <nan.h>
#include <node.h>

#include <iostream>

#define TAGLIB_STATIC
#include <taglib/tag.h>
#include <taglib/tlist.h>
#include <taglib/fileref.h>
#include <taglib/tfile.h>

using namespace std;
using namespace v8;
using namespace node;

NAN_METHOD(foo) {
  Nan::HandleScope scope;

  string path = *v8::String::Utf8Value(info[0]->ToString());
  string expected = "å æ ø ö ä ù ó ð.mp3";

  assert(path == expected);

  TagLib::FileRef f(path.c_str());
  TagLib::Tag *tag = f.tag();

  assert(tag);
}

void Init(v8::Local<v8::Object> exports, v8::Local<v8::Value> module, void *) {
  exports->Set(Nan::New("foo").ToLocalChecked(),
    Nan::New<v8::FunctionTemplate>(foo)->GetFunction());
}

NODE_MODULE(quxx, Init)
