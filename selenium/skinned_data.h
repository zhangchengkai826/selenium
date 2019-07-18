#pragma once
#include <Windows.h>
#include <vector>
#include <unordered_map>
#include <DirectXMath.h>

// A Keyframe defines the bone transformation at an instant in time.
struct Keyframe
{
	Keyframe();

	float TimePos;
	DirectX::XMFLOAT3 Translation;
	DirectX::XMFLOAT3 Scale;
	DirectX::XMFLOAT4 RotationQuat;
};


// A BoneAnimation is defined by a list of keyframes. For time
// values inbetween two keyframes, we interpolate between the
// two nearest keyframes that bound the time.  
//
// We assume an animation always has two keyframes.
struct BoneAnimation
{
	float GetEndTime()const;
	void Interpolate(float timePos, DirectX::XMFLOAT4X4& toParentTransform)const;

	std::vector<Keyframe> Keyframes;
};

// Examples of AnimationClips are "Walk", "Run", "Attack", "Defend".
// An AnimationClip requires a BoneAnimation for every bone to form
// the animation clip.    
struct AnimationClip
{
	float GetClipEndTime()const;
	void Interpolate(float timePos, std::vector<DirectX::XMFLOAT4X4>& toParentTransforms)const;

	std::vector<BoneAnimation> BoneAnimations;
};

class SkinnedData
{
public:
	UINT BoneCount()const;
	void Set(
		std::vector<int>& boneHierarchy,
		std::vector<DirectX::XMFLOAT4X4>& boneOffsets,
		std::unordered_map<std::string, AnimationClip>& animationClips);

	float GetClipEndTime(const std::string& clipName)const;

	// In a real project, you'd want to cache the result if there was a chance
	// that you were calling this several times with the same clipName at 
	// the same timePos.
	void GetFinalTransforms(const std::string& clipName, float timePos,
		std::vector<DirectX::XMFLOAT4X4>& finalTransforms)const;

private:
	// Gives parentIndex of ith bone.
	std::vector<int> mBoneHierarchy;

	std::vector<DirectX::XMFLOAT4X4> mBoneOffsets;

	std::unordered_map<std::string, AnimationClip> mAnimationClips;
};