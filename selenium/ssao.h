#pragma once
#include <d3d12.h>
#include <wrl/client.h>
#include <DirectXMath.h>

class SSAO {
public:
	SSAO(ID3D12Device* device,
		ID3D12GraphicsCommandList* cmdList,
		UINT width, UINT height);

	// Call when the backbuffer is resized.  
	void OnResize(UINT newWidth, UINT newHeight);

private:
	void BuildResources();
	void BuildOffsetVectors();
	void BuildRandomVectorTexture(ID3D12GraphicsCommandList* cmdList);

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

	DirectX::XMFLOAT4 mOffsets[14];
};