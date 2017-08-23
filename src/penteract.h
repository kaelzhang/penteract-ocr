#pragma once

#include <napi.h>

class Penteract : public Napi::ObjectWrap<Penteract>
{
public:
    static void Initialize(Napi::Env&, Napi::Object&);

    Penteract(const Napi::CallbackInfo&);
    Napi::Value Greet(const Napi::CallbackInfo&);

private:
    Napi::Reference<Napi::String> _greeterName;
};