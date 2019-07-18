#pragma once
#include <d3d12.h>
#include <wrl/client.h>
#include "d3dx12.h"

class ShadowMap {
public:
	ShadowMap(ID3D12Device *device, UINT width, UINT height);
	ShadowMap(const ShadowMap &rhs) = delete;
	ShadowMap &operator=(const ShadowMap &rhs) = delete;
	
	UINT Width()const;
	UINT Height()const;

	void BuildDescriptors(
		CD3DX12_CPU_DESCRIPTOR_HANDLE hCpuSrv,
		CD3DX12_GPU_DESCRIPTOR_HANDLE hGpuSrv,
		CD3DX12_CPU_DESCRIPTOR_HANDLE hCpuDsv);

private:
	void BuildResource();
	void BuildDescriptors();

private:
	ID3D12Device* md3dDevice = nullptr;
	
	UINT mWidth = 0;
	UINT mHeight = 0;

	D3D12_VIEWPORT mViewport;
	D3D12_RECT mScissorRect;

	DXGI_FORMAT mFormat = DXGI_FORMAT_R24G8_TYPELESS;

	Microsoft::WRL::ComPtr<ID3D12Resource> mShadowMap = nullptr;

	CD3DX12_CPU_DESCRIPTOR_HANDLE mhCpuSrv;
	CD3DX12_GPU_DESCRIPTOR_HANDLE mhGpuSrv;
	CD3DX12_CPU_DESCRIPTOR_HANDLE mhCpuDsv;
};