#pragma once
#include "skinned_data.h"
#include <DirectXMath.h>

struct SkinnedController
{
	SkinnedData* Data = nullptr;
	std::vector<DirectX::XMFLOAT4X4> FinalTransforms;
	std::string ClipName;
	float TimePos = 0.0f;

	// Called every frame and increments the time position, interpolates the 
    // animations for each bone based on the current animation clip, and 
    // generates the final transforms which are ultimately set for 
	// processing in the vertex shader.
	void UpdateAnimation(float dt)
	{
		TimePos += dt;

		// Loop animation
		if (TimePos > Data->GetClipEndTime(ClipName))
			TimePos = 0.0f;

		// Compute the final transforms for this time position.
		Data->GetFinalTransforms(ClipName, TimePos, FinalTransforms);
	}
};
