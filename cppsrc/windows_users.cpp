#include "windows_users.h"
#include <vector>


std::vector<std::string> v = {"One", "Two", "Three"};

std::vector<std::string> windows_users::getUsers(){
    return v;
}

Napi::Array windows_users::GetUsersWrapped(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    Napi::Array returnedArray = Napi::Array::New(env);
    int i = 0;
    for(auto x: v){ 
	returnedArray.Set(uint32_t(i), x); 
        i++;
    } 

    return returnedArray;
}


Napi::Object windows_users::Init(Napi::Env env, Napi::Object exports) {
    exports.Set("getUsers", Napi::Function::New(env, windows_users::GetUsersWrapped));
    return exports;
}
