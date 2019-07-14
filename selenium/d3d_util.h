#pragma once
#include <Windows.h>
#include <string>

#ifdef ThrowIfFailed
#error ThrowIfFailed redefined!
#endif // ThrowIfFailed

#define ThrowIfFailed(x)                                              \
{                                                                     \
    HRESULT hr__ = (x);                                               \
    std::wstring wfn = AnsiToWString(__FILE__);                       \
    if(FAILED(hr__)) { throw D3DException(hr__, L#x, wfn, __LINE__); } \
}

inline std::wstring AnsiToWString(const std::string &str)
{
	WCHAR buffer[512];
	MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, buffer, 512);
	return std::wstring(buffer);
}

class D3DException
{
public:
	D3DException() = default;
	D3DException(HRESULT hr, const std::wstring& functionName, const std::wstring& filename, int lineNumber);

	std::wstring ToString()const;

	HRESULT ErrorCode = S_OK;
	std::wstring FunctionName;
	std::wstring Filename;
	int LineNumber = -1;
};
