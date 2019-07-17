#pragma once
#include "d3d_app.h"
#include <DirectXCollision.h>
#include "camera.h"
#include "shadow_map.h"
#include <memory>
#include "ssao.h"
#include <string>
#include "m3d_loader.h"
#include "skinned_data.h"
#include "skinned_mesh_controller.h"
#include "mesh_geometry.h"
#include "texture.h"
#include <array>
#include "d3dx12.h"
#include <wrl/client.h>
#include <vector>
#include "material.h"
#include "render_item.h"
#include "render_layer.h"
#include "frame_resource.h"

class SeleniumApp : public D3DApp {
public:
	SeleniumApp(HINSTANCE hInstance);
	SeleniumApp(const SeleniumApp &rhs) = delete;
	SeleniumApp &operator=(const SeleniumApp &rhs) = delete;

	bool Initialize()override;

private:
	void CreateRtvAndDsvDescriptorHeaps()override;

	void LoadSkinnedModel();
	void LoadTextures();
	void BuildRootSignature();
	void BuildSsaoRootSignature();
	void BuildDescriptorHeaps();
	void BuildShadersAndInputLayout();
	void BuildShapeGeometry();
	void BuildMaterials();
	void BuildRenderItems();
	void BuildFrameResources();
	void BuildPSOs();

	std::array<const CD3DX12_STATIC_SAMPLER_DESC, 7> GetStaticSamplers();

	CD3DX12_CPU_DESCRIPTOR_HANDLE GetCbvSrvUavCpuDescriptorHandle(int indexInHeap)const;
	CD3DX12_GPU_DESCRIPTOR_HANDLE GetCbvSrvUavGpuDescriptorHandle(int indexInHeap)const;
	CD3DX12_CPU_DESCRIPTOR_HANDLE GetDsvCpuDescriptorHandle(int indexInHeap)const;
	CD3DX12_CPU_DESCRIPTOR_HANDLE GetRtvCpuDescriptorHandle(int indexInHeap)const;

private:
	static const int NumFrameResources = 3;

	DirectX::BoundingSphere mSceneBounds;

	Camera mCamera;

	std::unique_ptr<ShadowMap> mShadowMap;

	std::unique_ptr<Ssao> mSsao;

	std::string mSkinnedModelFilename = "Models\\soldier.m3d";
	std::vector<M3DLoader::Subset> mSkinnedSubsets;
	std::vector<M3DLoader::MaterialInfo> mSkinnedMatInfo;
	std::vector<std::string> mSkinnedTexNames;
	UINT mSkinnedTexHeapIndexStart = 0;
	SkinnedData mSkinnedData;
	std::unique_ptr<SkinnedMeshController> mSkinnedMeshController;

	std::unordered_map<std::string, std::unique_ptr<MeshGeometry>> mGeometries;
	std::unordered_map<std::string, std::unique_ptr<Texture>> mTextures;
	std::unordered_map<std::string, Microsoft::WRL::ComPtr<ID3DBlob>> mShaders;
	std::unordered_map<std::string, std::unique_ptr<Material>> mMaterials;
	
	// List of all the render items.
	std::vector<std::unique_ptr<RenderItem>> mAllRitems;

	// Render items divided by PSO.
	std::vector<RenderItem *> mRitemLayer[(int)RenderLayer::Count];

	std::vector<D3D12_INPUT_ELEMENT_DESC> mInputLayout;
	std::vector<D3D12_INPUT_ELEMENT_DESC> mSkinnedInputLayout;

	Microsoft::WRL::ComPtr<ID3D12RootSignature> mRootSignature = nullptr;
	Microsoft::WRL::ComPtr<ID3D12RootSignature> mSsaoRootSignature = nullptr;

	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> mCbvSrvUavHeap;

	UINT mSkyTexHeapIndex = 0;
	UINT mShadowMapHeapIndex = 0;
	UINT mSsaoHeapIndexStart = 0;

	CD3DX12_GPU_DESCRIPTOR_HANDLE mNullCubeSrvGpuHandle;
	UINT mNullCubeSrvIndex = 0;
	UINT mNullTexSrvIndex1 = 0;
	UINT mNullTexSrvIndex2 = 0;

	std::vector<std::unique_ptr<FrameResource>> mFrameResources;

	std::unordered_map<std::string, Microsoft::WRL::ComPtr<ID3D12PipelineState>> mPSOs;
};