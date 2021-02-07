#include <napi.h>
#include <vector>

namespace windows_users {

    std::vector<std::wstring> getUsers();

    Napi::Array GetUsersWrapped(const Napi::CallbackInfo& info);

    Napi::Object Init(Napi::Env env, Napi::Object exports);
    
}
