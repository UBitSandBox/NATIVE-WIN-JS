//
// Created by ubit-gng on 08.07.2020.
//
#include <napi.h>
#include "Impersonator.h"

Napi::Object CreateObject(const Napi::CallbackInfo& info) {
    return Impersonator::NewInstance(info.Env(), info[0], info[1], info[2]);
}

Napi::Object InitAll(Napi::Env env, Napi::Object exports) {
    Napi::Object new_exports =
            Napi::Function::New(env, CreateObject, "CreateObject");
    return Impersonator::Init(env, new_exports);
}

NODE_API_MODULE(addon, InitAll)
