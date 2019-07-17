#pragma once
#include <Windows.h>
#include <DirectXMath.h>
#include <string>
#include <vector>
#include "skinned_data.h"

class M3DLoader
{
public:
	struct Vertex
	{
		Vertex() {}
		Vertex(
			const DirectX::XMFLOAT3& p,
			const DirectX::XMFLOAT3& n,
			const DirectX::XMFLOAT3& t,
			const DirectX::XMFLOAT2& uv) :
			Pos(p),
			Normal(n),
			TangentU(t),
			TexC(uv) {}
		Vertex(
			float px, float py, float pz,
			float nx, float ny, float nz,
			float tx, float ty, float tz,
			float u, float v) :
			Pos(px, py, pz),
			Normal(nx, ny, nz),
			TangentU(tx, ty, tz),
			TexC(u, v) {}
		DirectX::XMFLOAT3 Pos;
		DirectX::XMFLOAT3 Normal;
		DirectX::XMFLOAT2 TexC;
		DirectX::XMFLOAT3 TangentU;
	};

	struct SkinnedVertex
	{
		DirectX::XMFLOAT3 Pos;
		DirectX::XMFLOAT3 Normal;
		DirectX::XMFLOAT2 TexC;
		DirectX::XMFLOAT3 TangentU;
		DirectX::XMFLOAT4 BoneWeights;
		BYTE BoneIndices[4];
	};

	struct Subset
	{
		UINT Id = -1;
		UINT VertexStart = 0;
		UINT VertexCount = 0;
		UINT FaceStart = 0;
		UINT FaceCount = 0;
	};

	struct M3dMaterial
	{
		std::string Name;

		DirectX::XMFLOAT4 DiffuseAlbedo = { 1.0f, 1.0f, 1.0f, 1.0f };
		DirectX::XMFLOAT3 FresnelR0 = { 0.01f, 0.01f, 0.01f };
		float Roughness = 0.8f;
		bool AlphaClip = false;

		std::string MaterialTypeName;
		std::string DiffuseMapName;
		std::string NormalMapName;
	};

	bool LoadM3d(const std::string &filename,
		std::vector<SkinnedVertex> &vertices,
		std::vector<USHORT> &indices,
		std::vector<Subset> &subsets,
		std::vector<M3dMaterial> &mats,
		SkinnedData &skinnedData);

private:
	void ReadMaterials(std::ifstream& fin, UINT numMaterials, std::vector<M3dMaterial>& mats);
	void ReadSubsetTable(std::ifstream& fin, UINT numSubsets, std::vector<Subset>& subsets);
	void ReadSkinnedVertices(std::ifstream& fin, UINT numVertices, std::vector<SkinnedVertex>& vertices);
	void ReadTriangles(std::ifstream& fin, UINT numTriangles, std::vector<USHORT>& indices);
	void ReadBoneOffsets(std::ifstream& fin, UINT numBones, std::vector<DirectX::XMFLOAT4X4>& boneOffsets);
	void ReadBoneHierarchy(std::ifstream& fin, UINT numBones, std::vector<int>& boneHierarchy);
	void ReadAnimationClips(std::ifstream& fin, UINT numBones, UINT numAnimationClips, std::unordered_map<std::string, AnimationClip>& animationClips);
	void ReadBoneAnimation(std::ifstream& fin, UINT numBones, BoneAnimation& boneAnimation);
};
