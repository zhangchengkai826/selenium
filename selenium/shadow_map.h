#pragma once
#include <d3d12.h>
#include <wrl/client.h>

class ShadowMap {
public:
	ShadowMap(ID3D12Device *device, UINT width, UINT height);
	ShadowMap(const ShadowMap &rhs) = delete;
	ShadowMap &operator=(const ShadowMap &rhs) = delete;

private:
	void BuildResource();

private:
	ID3D12Device* md3dDevice = nullptr;
	
	UINT mWidth = 0;
	UINT mHeight = 0;

	D3D12_VIEWPORT mViewport;
	D3D12_RECT mScissorRect;

	DXGI_FORMAT mFormat = DXGI_FORMAT_R24G8_TYPELESS;

	Microsoft::WRL::ComPtr<ID3D12Resource> mShadowMap = nullptr;
};