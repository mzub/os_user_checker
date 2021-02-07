#include <napi.h>
#include "windows_users.h"

Napi::Object InitAll(Napi::Env env, Napi::Object exports) {
	return windows_users::Init(env, exports);
}

NODE_API_MODULE(NODE_GYP_MODULE_NAME, InitAll)
