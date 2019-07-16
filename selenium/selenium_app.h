#pragma once
#include "d3d_app.h"
#include <DirectXCollision.h>
#include "camera.h"

class SeleniumApp : public D3DApp {
public:
	SeleniumApp(HINSTANCE hInstance);
	SeleniumApp(const SeleniumApp &rhs) = delete;
	SeleniumApp& operator=(const SeleniumApp &rhs) = delete;

	bool Initialize()override;

private:
	DirectX::BoundingSphere mSceneBounds;

	Camera mCamera;
};