#ifndef UNICODE
#define UNICODE
#endif
#pragma comment(lib, "netapi32.lib")
using namespace std;
#include "windows_users.h"
#include <vector>
#include <stdio.h>
#include <assert.h>
#include <windows.h> 
#include <lm.h>


std::vector<std::wstring> windows_users::getUsers(){
	LPUSER_INFO_0 pBuf = NULL;
	LPUSER_INFO_0 pTmpBuf;
	DWORD dwLevel = 0;
	DWORD dwPrefMaxLen = MAX_PREFERRED_LENGTH;
	DWORD dwEntriesRead = 0;
	DWORD dwTotalEntries = 0;
	DWORD dwResumeHandle = 0;
	DWORD i;
	NET_API_STATUS nStatus;
	LPTSTR pszServerName = NULL;
	vector<wstring> usersList;

	do // begin do
	{
		nStatus = NetUserEnum((LPCWSTR) pszServerName,
				dwLevel,
				FILTER_NORMAL_ACCOUNT, // global users
				(LPBYTE*)&pBuf,
				dwPrefMaxLen,
				&dwEntriesRead,
				&dwTotalEntries,
				&dwResumeHandle);
		if ((nStatus == NERR_Success) || (nStatus == ERROR_MORE_DATA))
		{
			if ((pTmpBuf = pBuf) != NULL)
			{
				for (i = 0; (i < dwEntriesRead); i++)
				{
					assert(pTmpBuf != NULL);
					if (pTmpBuf == NULL)
					{
						fprintf(stderr, "An access violation has occurred\n");
						break;
					}
					usersList.push_back(pTmpBuf->usri0_name);
					pTmpBuf++;
				}
			}
		}
		else
			fprintf(stderr, "A system error has occurred: %d\n", nStatus);
		if (pBuf != NULL)
		{
			NetApiBufferFree(pBuf);
			pBuf = NULL;
		}
	}
	while (nStatus == ERROR_MORE_DATA); // end do
	if (pBuf != NULL)
		NetApiBufferFree(pBuf);

	return usersList;
}

Napi::Array windows_users::GetUsersWrapped(const Napi::CallbackInfo& info) {
	Napi::Env env = info.Env();
	Napi::Array returnedArray = Napi::Array::New(env);
	int i = 0;
	for(auto x: getUsers()){
		string str = std::string(x.begin(), x.end());		 
		returnedArray.Set(uint32_t(i), str); 
		i++;
	} 

	return returnedArray;
}


Napi::Object windows_users::Init(Napi::Env env, Napi::Object exports) {
	exports.Set("getUsers", Napi::Function::New(env, windows_users::GetUsersWrapped));
	return exports;
}
