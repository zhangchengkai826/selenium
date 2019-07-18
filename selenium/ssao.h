#pragma once
#include <d3d12.h>
#include <wrl/client.h>
#include <DirectXMath.h>
#include "d3dx12.h"
#include "frame_resource.h"

class Ssao {
public:
	Ssao(ID3D12Device* device,
		ID3D12GraphicsCommandList* cmdList,
		UINT width, UINT height);

	UINT AmbientMapWidth()const;
	UINT AmbientMapHeight()const;

	ID3D12Resource* NormalMap();
	ID3D12Resource* AmbientMap();

	CD3DX12_CPU_DESCRIPTOR_HANDLE NormalMapCpuRtv()const;
	CD3DX12_GPU_DESCRIPTOR_HANDLE NormalMapGpuSrv()const;
	CD3DX12_GPU_DESCRIPTOR_HANDLE AmbientMapGpuSrv()const;

	// Call when the backbuffer is resized.  
	void OnResize(UINT newWidth, UINT newHeight);

	void BuildDescriptors(
		ID3D12Resource* depthStencilBuffer,
		CD3DX12_CPU_DESCRIPTOR_HANDLE hCpuSrv,
		CD3DX12_GPU_DESCRIPTOR_HANDLE hGpuSrv,
		CD3DX12_CPU_DESCRIPTOR_HANDLE hCpuRtv,
		UINT cbvSrvUavDescriptorSize,
		UINT rtvDescriptorSize);
	void BuildDescriptors(ID3D12Resource* depthStencilBuffer);

	void SetPSOs(ID3D12PipelineState* ssaoPso, ID3D12PipelineState* ssaoBlurPso);

	void GetOffsetVectors(DirectX::XMFLOAT4 offsetVectors[14]);
	std::vector<float> CalcGaussWeights(float sigma);

	// Changes the render target to the Ambient render target and draws a fullscreen
	// quad to kick off the pixel shader to compute the AmbientMap.  We still keep the
	// main depth buffer binded to the pipeline, but depth buffer read/writes
	// are disabled, as we do not need the depth buffer computing the Ambient map.
	void ComputeSsao(
		ID3D12GraphicsCommandList* cmdList,
		FrameResource* currFrameResource,
		int blurCount);

private:
	void BuildResources();
	void BuildOffsetVectors();
	void BuildRandomVectorTexture(ID3D12GraphicsCommandList* cmdList);

	// Blurs the ambient map to smooth out the noise caused by only taking a
	// few random samples per pixel.  We use an edge preserving blur so that 
	// we do not blur across discontinuities--we want edges to remain edges.
	void BlurAmbientMap(ID3D12GraphicsCommandList* cmdList, FrameResource* currFrame, int blurCount);
	void BlurAmbientMap(ID3D12GraphicsCommandList* cmdList, bool horzBlur);

public:
	static const DXGI_FORMAT NormalMapFormat = DXGI_FORMAT_R16G16B16A16_FLOAT;
	static const DXGI_FORMAT AmbientMapFormat = DXGI_FORMAT_R16_UNORM;

	static const int MaxBlurRadius = 5;

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