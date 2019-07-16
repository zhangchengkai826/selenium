#include "camera.h"
#include <DirectXMath.h>

using namespace DirectX;

Camera::Camera() {
	SetLens(0.25f*MathHelper::Pi, 1.0f, 1.0f, 1000.0f);
}

void Camera::SetLens(float fovY, float aspect, float zn, float zf) {
	// cache properties
	mFovY = fovY;
	mAspect = aspect;
	mNearZ = zn;
	mFarZ = zf;

	mNearWindowHeight = 2.0f * mNearZ * tanf(0.5f*mFovY);
	mFarWindowHeight = 2.0f * mFarZ * tanf(0.5f*mFovY);

	XMMATRIX P = XMMatrixPerspectiveFovLH(mFovY, mAspect, mNearZ, mFarZ);
	XMStoreFloat4x4(&mProj, P);
}

void Camera::SetPosition(float x, float y, float z)
{
	mPosition = XMFLOAT3(x, y, z);
	mViewDirty = true;
}
