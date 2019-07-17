#pragma once
#include "skinned_data.h"
#include <DirectXMath.h>

struct SkinnedMeshController
{
	SkinnedData* SkinnedData = nullptr;
	std::vector<DirectX::XMFLOAT4X4> FinalTransforms;
	std::string ClipName;
	float TimePos = 0.0f;
};
