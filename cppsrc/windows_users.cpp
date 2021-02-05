#include "windows_users.h"

std::string windows_users::getUsers(){
    return "Hello World";
}

Napi::String windows_users::GetUsersWrapped(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    Napi::String returnValue = Napi::String::New(env, windows_users::getUsers());
    return returnValue;
}


Napi::Object windows_users::Init(Napi::Env env, Napi::Object exports) {
    exports.Set("getUsers", Napi::Function::New(env, windows_users::GetUsersWrapped));
    return exports;
}
