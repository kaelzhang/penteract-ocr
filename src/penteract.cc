#include "penteract.h"

using namespace Napi;

void Penteract::Initialize(Napi::Env& env, Object& target) {
    Napi::Function constructor = DefineClass(env, "Penteract", {
        InstanceMethod("greet", &Penteract::Greet)
    });

    target.Set("Penteract", constructor);
}

Napi::Value Penteract::Greet(const Napi::CallbackInfo& info) {
    if (!info[0].IsString())
    {
        throw Error::New(info.Env(), "You need to introduce yourself to greet");
    }

    String name = info[0].As<String>();

    printf("Hello %s\n", name.Utf8Value().c_str());
    printf("I am %s\n", this->_greeterName.Value().Utf8Value().c_str());

    return this->_greeterName.Value();
}

Penteract::Penteract(const Napi::CallbackInfo& info) {
    if (!info[0].IsString())
    {
        throw Error::New(info.Env(), "You must name me");
    }

    this->_greeterName = Persistent(info[0].As<String>());
}

void Init(Env env, Object exports, Object module) {
    Penteract::Initialize(env, exports);
}

NODE_API_MODULE(addon, Init)