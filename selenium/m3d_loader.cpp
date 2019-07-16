#include "m3d_loader.h"
#include <fstream>
#include <string>
#include <DirectXMath.h>

using namespace DirectX;

bool M3DLoader::LoadM3d(const std::string &filename,
	std::vector<SkinnedVertex> &vertices,
	std::vector<USHORT> &indices,
	std::vector<Subset> &subsets,
	std::vector<M3dMaterial> &mats,
	SkinnedData &skinnedData) {
	
	std::ifstream fin(filename);

	UINT numMaterials = 0;
	UINT numVertices = 0;
	UINT numTriangles = 0;
	UINT numBones = 0;
	UINT numAnimationClips = 0;

	std::string ignore;

	if (fin)
	{
		fin >> ignore; // file header text
		fin >> ignore >> numMaterials;
		fin >> ignore >> numVertices;
		fin >> ignore >> numTriangles;
		fin >> ignore >> numBones;
		fin >> ignore >> numAnimationClips;

		std::vector<XMFLOAT4X4> boneOffsets;
		std::vector<int> boneHierarchy;
		std::unordered_map<std::string, AnimationClip> animationClips;

		ReadMaterials(fin, numMaterials, mats);

		return true;
	}
	return false;
}

void M3DLoader::ReadMaterials(std::ifstream &fin, UINT numMaterials, std::vector<M3dMaterial> &mats) {
	std::string ignore;
	mats.resize(numMaterials);

	fin >> ignore; // materials header text
	for (UINT i = 0; i < numMaterials; ++i)
	{
		fin >> ignore >> mats[i].Name;
		fin >> ignore >> mats[i].DiffuseAlbedo.x >> mats[i].DiffuseAlbedo.y >> mats[i].DiffuseAlbedo.z;
		fin >> ignore >> mats[i].FresnelR0.x >> mats[i].FresnelR0.y >> mats[i].FresnelR0.z;
		fin >> ignore >> mats[i].Roughness;
		fin >> ignore >> mats[i].AlphaClip;
		fin >> ignore >> mats[i].MaterialTypeName;
		fin >> ignore >> mats[i].DiffuseMapName;
		fin >> ignore >> mats[i].NormalMapName;
	}
}