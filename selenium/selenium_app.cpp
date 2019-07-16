#include "selenium_app.h"
#include <DirectXMath.h>
#include "d3d_util.h"
#include <vector>
#include "m3d_loader.h"
#include "mesh_geometry.h"
#include <d3dcompiler.h>

using namespace DirectX;

SeleniumApp::SeleniumApp(HINSTANCE hInstance)
	: D3DApp(hInstance)
{
	// Estimate the scene bounding sphere manually since we know how the scene was constructed.
	// The grid is the "widest object" with a width of 20 and depth of 30.0f, and centered at
	// the world space origin.  In general, you need to loop over every world space vertex
	// position and compute the bounding sphere.
	mSceneBounds.Center = XMFLOAT3(0.0f, 0.0f, 0.0f);
	mSceneBounds.Radius = sqrtf(10.0f*10.0f + 15.0f*15.0f);
}

bool SeleniumApp::Initialize()
{
	if (!D3DApp::Initialize())
		return false;

	// Reset the command list to prep for initialization commands.
	ThrowIfFailed(mCmdList->Reset(mCmdAllocator.Get(), nullptr));
	
	mCamera.SetPosition(0.0f, 2.0f, -15.0f);

	mShadowMap = std::make_unique<ShadowMap>(md3dDevice.Get(), 2048, 2048);

	mSSAO = std::make_unique<SSAO>(
		md3dDevice.Get(),
		mCmdList.Get(),
		mClientWidth, mClientHeight);

	LoadSkinnedModel();

	return true;
}

void SeleniumApp::LoadSkinnedModel() {
	std::vector<M3DLoader::SkinnedVertex> vertices;
	std::vector<std::uint16_t> indices;

	M3DLoader m3dLoader;
	m3dLoader.LoadM3d(mSkinnedModelFilename, vertices, indices,
		mSkinnedSubsets, mSkinnedMats, mSkinnedData);

	mSkinnedModel = std::make_unique<SkinnedModel>();
	mSkinnedModel->SkinnedData = &mSkinnedData;
	mSkinnedModel->FinalTransforms.resize(mSkinnedData.BoneCount());
	mSkinnedModel->ClipName = "Take1";
	mSkinnedModel->TimePos = 0.0f;

	const UINT vbByteSize = (UINT)vertices.size() * sizeof(M3DLoader::SkinnedVertex);
	const UINT ibByteSize = (UINT)indices.size() * sizeof(std::uint16_t);

	auto geo = std::make_unique<MeshGeometry>();
	geo->Name = mSkinnedModelFilename;

	ThrowIfFailed(D3DCreateBlob(vbByteSize, &geo->VertexBufferCPU));
	CopyMemory(geo->VertexBufferCPU->GetBufferPointer(), vertices.data(), vbByteSize);

	ThrowIfFailed(D3DCreateBlob(ibByteSize, &geo->IndexBufferCPU));
	CopyMemory(geo->IndexBufferCPU->GetBufferPointer(), indices.data(), ibByteSize);

	geo->VertexBufferGPU = D3DUtil::CreateDefaultBuffer(md3dDevice.Get(),
		mCmdList.Get(), vertices.data(), vbByteSize, geo->VertexBufferUploader);

	geo->IndexBufferGPU = D3DUtil::CreateDefaultBuffer(md3dDevice.Get(),
		mCmdList.Get(), indices.data(), ibByteSize, geo->IndexBufferUploader);

	geo->VertexStrideInBytes = sizeof(M3DLoader::SkinnedVertex);
	geo->VertexBufferSizeInBytes = vbByteSize;
	geo->IndexFormat = DXGI_FORMAT_R16_UINT;
	geo->IndexBufferSizeInBytes = ibByteSize;

	for (UINT i = 0; i < (UINT)mSkinnedSubsets.size(); ++i)
	{
		SubmeshGeometry submesh;
		std::string name = "sm_" + std::to_string(i);

		submesh.IndexCount = (UINT)mSkinnedSubsets[i].FaceCount * 3;
		submesh.StartIndexLocation = mSkinnedSubsets[i].FaceStart * 3;
		submesh.BaseVertexLocation = 0;

		geo->DrawArgs[name] = submesh;
	}

	mGeometries[geo->Name] = std::move(geo);
}