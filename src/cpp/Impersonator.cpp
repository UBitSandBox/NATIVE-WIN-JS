//
// Created by ubit-gng on 08.07.2020.
//
#include "Impersonator.h"

using namespace Napi;

Napi::Object Impersonator::Init(Napi::Env env, Napi::Object exports) {

    Napi::Function func =
            DefineClass(env,
                    "Impersonator",{
                InstanceMethod("impersonateUser", &Impersonator::ImpersonateUser),
                InstanceMethod("stopImpersonation", &Impersonator::StopImpersonation),
                InstanceMethod("closeUserToken", &Impersonator::CloseUserToken)
            });

    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);

    exports.Set("Impersonator", func);
    return exports;
}

/***
 * Constructor
 * @param info
 */
Impersonator::Impersonator(const Napi::CallbackInfo &info)
    : Napi::ObjectWrap<Impersonator>(info){
    Napi::Env env = info.Env();

    int length = info.Length();
    if(length < 3 || (!info[0].IsString() && !info[1].IsString() && !info[2].IsString())){
        Napi::TypeError::New(env, "3 String Parameters are expected").ThrowAsJavaScriptException();
        return;
    }

    this->name_ = to_wstring(info[0]);
    this->password_ = to_wstring(info[1]);
    this->domain_ = to_wstring(info[2]);
}

/**
 * Factory
 * @param env
 * @param arg0
 * @param arg1
 * @param arg2
 * @return
 */
Napi::Object Impersonator::NewInstance(Napi::Env env, Napi::Value arg0, Napi::Value arg1, Napi::Value arg2) {
    Napi::EscapableHandleScope scope(env);
    Napi::Object obj = env.GetInstanceData<Napi::FunctionReference>()->New({arg0, arg1, arg2});
    return scope.Escape(napi_value(obj)).ToObject();
}

/***
 * Impersonating user, calling COM Functions
 * LogonUserW and ImpersonateLoggedOnUser
 * @param info
 */
void Impersonator::ImpersonateUser(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();

    int length = info.Length();
    if(length < 2 || (!info[0].IsNumber() && !info[1].IsNumber())){
        Napi::TypeError::New(env, "2 Int Parameters are expected").ThrowAsJavaScriptException();
        return;
    }

    uint32_t type = info[0].As<Napi::Number>().Uint32Value();
    uint32_t provider = info[1].As<Napi::Number>().Uint32Value();

    if(this->token_ != NULL){
        Impersonator::CloseUserToken(info);
    }

    auto hr = LogonUserW(
            this->name_.c_str(),
            this->domain_.c_str(),
            this->password_.c_str(),
            type,
            provider,
            this->token_);

    if (!hr) {
        createWindowsError(env, GetLastError(), "LogonUserW").ThrowAsJavaScriptException();
        return;
    }

    if (!ImpersonateLoggedOnUser(&this->token_)) {
        createWindowsError(env, GetLastError(), "ImpersonateLoggedOnUser").ThrowAsJavaScriptException();
    }
}

/***
 * Stopping Impersonation
 */
void Impersonator::StopImpersonation(const Napi::CallbackInfo &info){
    Napi::Env env = info.Env();

    if (!RevertToSelf()) {
        createWindowsError(env, GetLastError(), "RevertToSelf").ThrowAsJavaScriptException();
        return;
    }

    Impersonator::CloseUserToken(info);
}

/**
 * Closing user token
 * @param env
 */
void Impersonator::CloseUserToken(const Napi::CallbackInfo &info){
    Napi::Env env = info.Env();

    if(&this->token_ == NULL){
        return;
    }

    if (!CloseHandle(&this->token_)) {
        createWindowsError(env, GetLastError(), "CloseHandle").ThrowAsJavaScriptException();
        return;
    }
}