#pragma once
#include <d3d12.h>
#include <wrl/client.h>
#include <DirectXMath.h>
#include "d3dx12.h"

class Ssao {
public:
	Ssao(ID3D12Device* device,
		ID3D12GraphicsCommandList* cmdList,
		UINT width, UINT height);

	// Call when the backbuffer is resized.  
	void OnResize(UINT newWidth, UINT newHeight);

	void BuildDescriptors(
		ID3D12Resource* depthStencilBuffer,
		CD3DX12_CPU_DESCRIPTOR_HANDLE hCpuSrv,
		CD3DX12_GPU_DESCRIPTOR_HANDLE hGpuSrv,
		CD3DX12_CPU_DESCRIPTOR_HANDLE hCpuRtv,
		UINT cbvSrvUavDescriptorSize,
		UINT rtvDescriptorSize);

	void SetPSOs(ID3D12PipelineState* ssaoPso, ID3D12PipelineState* ssaoBlurPso);

private:
	void BuildResources();
	void BuildOffsetVectors();
	void BuildRandomVectorTexture(ID3D12GraphicsCommandList* cmdList);

	void BuildDescriptors(ID3D12Resource* depthStencilBuffer);

public:
	static const DXGI_FORMAT NormalMapFormat = DXGI_FORMAT_R16G16B16A16_FLOAT;
	static const DXGI_FORMAT AmbientMapFormat = DXGI_FORMAT_R16_UNORM;

private:
	ID3D12Device* md3dDevice;

	UINT mRenderTargetWidth = 0;
	UINT mRenderTargetHeight = 0;

	D3D12_VIEWPORT mViewport;
	D3D12_RECT mScissorRect;

	Microsoft::WRL::ComPtr<ID3D12Resource> mNormalMap;
	Microsoft::WRL::ComPtr<ID3D12Resource> mAmbientMap0;
	Microsoft::WRL::ComPtr<ID3D12Resource> mAmbientMap1;

	Microsoft::WRL::ComPtr<ID3D12Resource> mRandomVectorMap;
	Microsoft::WRL::ComPtr<ID3D12Resource> mRandomVectorMapUploadBuffer;

	DirectX::XMFLOAT4 mOffsetVectors[14];
	
	CD3DX12_CPU_DESCRIPTOR_HANDLE mhNormalMapCpuSrv;
	CD3DX12_GPU_DESCRIPTOR_HANDLE mhNormalMapGpuSrv;
	CD3DX12_CPU_DESCRIPTOR_HANDLE mhNormalMapCpuRtv;

	CD3DX12_CPU_DESCRIPTOR_HANDLE mhDepthMapCpuSrv;
	CD3DX12_GPU_DESCRIPTOR_HANDLE mhDepthMapGpuSrv;

	CD3DX12_CPU_DESCRIPTOR_HANDLE mhRandomVectorMapCpuSrv;
	CD3DX12_GPU_DESCRIPTOR_HANDLE mhRandomVectorMapGpuSrv;

	// Need two for ping-ponging during blur.
	CD3DX12_CPU_DESCRIPTOR_HANDLE mhAmbientMap0CpuSrv;
	CD3DX12_GPU_DESCRIPTOR_HANDLE mhAmbientMap0GpuSrv;
	CD3DX12_CPU_DESCRIPTOR_HANDLE mhAmbientMap0CpuRtv;

	CD3DX12_CPU_DESCRIPTOR_HANDLE mhAmbientMap1CpuSrv;
	CD3DX12_GPU_DESCRIPTOR_HANDLE mhAmbientMap1GpuSrv;
	CD3DX12_CPU_DESCRIPTOR_HANDLE mhAmbientMap1CpuRtv;

	ID3D12PipelineState* mPso = nullptr;
	ID3D12PipelineState* mBlurPso = nullptr;
};