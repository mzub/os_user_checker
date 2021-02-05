#include <napi.h>

namespace windows_users {

    std::string getUsers();
    Napi::String GetUsersWrapped(const Napi::CallbackInfo& info);

    Napi::Object Init(Napi::Env env, Napi::Object exports);
    
}
