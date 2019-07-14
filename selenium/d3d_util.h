#pragma once
#include <Windows.h>
#include <string>

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
