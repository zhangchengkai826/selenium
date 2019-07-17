#pragma once
#include "math_helper.h"

class Camera {
public:
	Camera();

	void SetPosition(float x, float y, float z);

	// Set frustum.
	void SetLens(float fovY, float aspect, float zn, float zf);

	// Rotate the camera.
	void Pitch(float angle);
	void RotateY(float angle);

private:
	// Camera coordinate system with coordinates relative to world space.
	DirectX::XMFLOAT3 mPosition = { 0.0f, 0.0f, 0.0f };
	DirectX::XMFLOAT3 mRight = { 1.0f, 0.0f, 0.0f };
	DirectX::XMFLOAT3 mUp = { 0.0f, 1.0f, 0.0f };
	DirectX::XMFLOAT3 mLook = { 0.0f, 0.0f, 1.0f };

	// Cache frustum properties.
	float mFovY = 0.0f;
	float mAspect = 0.0f;
	float mNearZ = 0.0f;
	float mFarZ = 0.0f;
	float mNearWindowHeight = 0.0f;
	float mFarWindowHeight = 0.0f;

	bool mViewDirty = true;

	DirectX::XMFLOAT4X4 mProj = MathHelper::Identity4x4();
};