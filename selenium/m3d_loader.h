#pragma once
#include <Windows.h>
#include <DirectXMath.h>
#include <string>
#include <vector>
#include "skinned_data.h"
#include "vertex.h"

class M3DLoader
{
public:
	struct Subset
	{
		UINT Id = -1;
		UINT VertexStart = 0;
		UINT VertexCount = 0;
		UINT FaceStart = 0;
		UINT FaceCount = 0;
	};

	struct MaterialInfo
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
		std::vector<MaterialInfo> &mats,
		SkinnedData &skinnedData);

private:
	void ReadMaterials(std::ifstream& fin, UINT numMaterials, std::vector<MaterialInfo>& mats);
	void ReadSubsetTable(std::ifstream& fin, UINT numSubsets, std::vector<Subset>& subsets);
	void ReadSkinnedVertices(std::ifstream& fin, UINT numVertices, std::vector<SkinnedVertex>& vertices);
	void ReadTriangles(std::ifstream& fin, UINT numTriangles, std::vector<USHORT>& indices);
	void ReadBoneOffsets(std::ifstream& fin, UINT numBones, std::vector<DirectX::XMFLOAT4X4>& boneOffsets);
	void ReadBoneHierarchy(std::ifstream& fin, UINT numBones, std::vector<int>& boneHierarchy);
	void ReadAnimationClips(std::ifstream& fin, UINT numBones, UINT numAnimationClips, std::unordered_map<std::string, AnimationClip>& animationClips);
	void ReadBoneAnimation(std::ifstream& fin, UINT numBones, BoneAnimation& boneAnimation);
};
