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
#include "model.h"
#include "mesh_geometry.h"
#include "texture.h"
#include <array>
#include "d3dx12.h"
#include <wrl/client.h>

class SeleniumApp : public D3DApp {
public:
	SeleniumApp(HINSTANCE hInstance);
	SeleniumApp(const SeleniumApp &rhs) = delete;
	SeleniumApp &operator=(const SeleniumApp &rhs) = delete;

	bool Initialize()override;

private:
	void LoadSkinnedModel();
	void LoadTextures();
	void BuildRootSignature();
	
	std::array<const CD3DX12_STATIC_SAMPLER_DESC, 7> GetStaticSamplers();

private:
	DirectX::BoundingSphere mSceneBounds;

	Camera mCamera;

	std::unique_ptr<ShadowMap> mShadowMap;

	std::unique_ptr<SSAO> mSSAO;

	std::string mSkinnedModelFilename = "Models\\soldier.m3d";
	std::vector<M3DLoader::Subset> mSkinnedSubsets;
	std::vector<M3DLoader::M3dMaterial> mSkinnedMats;
	std::vector<std::string> mSkinnedTextureNames;
	SkinnedData mSkinnedData;
	std::unique_ptr<SkinnedModel> mSkinnedModel;

	std::unordered_map<std::string, std::unique_ptr<MeshGeometry>> mGeometries;
	std::unordered_map<std::string, std::unique_ptr<Texture>> mTextures;

	Microsoft::WRL::ComPtr<ID3D12RootSignature> mRootSignature = nullptr;
};