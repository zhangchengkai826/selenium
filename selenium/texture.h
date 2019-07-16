#pragma once
#include <string>
#include <d3d12.h>
#include <wrl/client.h>

struct Texture
{
	// Unique name for lookup.
	std::string Name;

	std::wstring Filename;

	Microsoft::WRL::ComPtr<ID3D12Resource> Resource = nullptr;
	Microsoft::WRL::ComPtr<ID3D12Resource> Uploader = nullptr;
};