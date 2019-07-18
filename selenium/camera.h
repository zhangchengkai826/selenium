#pragma once
#include "math_helper.h"

class Camera {
public:
	Camera();

	DirectX::XMFLOAT3 GetPosition3f()const;
	void SetPosition(float x, float y, float z);

	// Set frustum.
	void SetLens(float fovY, float aspect, float zn, float zf);

	// Rotate the camera.
	void Pitch(float angle);
	void RotateY(float angle);

	// Strafe/Walk the camera a distance d.
	void Strafe(float d);
	void Walk(float d);

	// After modifying camera position/orientation, call to rebuild the view matrix.
	void UpdateViewMatrix();

	// Get View/Proj matrices.
	DirectX::XMMATRIX GetView()const;
	DirectX::XMMATRIX GetProj()const;

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

	// Cache View/Proj matrices.
	DirectX::XMFLOAT4X4 mView = MathHelper::Identity4x4();
	DirectX::XMFLOAT4X4 mProj = MathHelper::Identity4x4();
};