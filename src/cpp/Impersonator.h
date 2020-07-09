//
// Created by ubit-gng on 08.07.2020.
//

#ifndef NATIVE_WIN_JS_IMPERSONATOR_H
#define NATIVE_WIN_JS_IMPERSONATOR_H

#include <napi.h>
#include <Windows.h>

#include <codecvt>
#include <vector>

#include "helper.h"

#pragma comment(lib, "netapi32.lib")
#pragma comment(lib, "userenv.lib")

class Impersonator : public Napi::ObjectWrap<Impersonator> {
    public:
        static Napi::Object Init(Napi::Env env, Napi::Object exports);
        static Napi::Object NewInstance(Napi::Env env, Napi::Value arg0, Napi::Value arg1, Napi::Value arg2);
        Impersonator(const Napi::CallbackInfo& info);
        void ImpersonateUser(const Napi::CallbackInfo& info);
        void StopImpersonation(const Napi::CallbackInfo& info);

    private:
        void CloseUserToken(const Napi::CallbackInfo& info);

    std::wstring domain_;
    std::wstring name_;
    std::wstring password_;

    HANDLE token_;
};


#endif //NATIVE_WIN_JS_IMPERSONATOR_H
