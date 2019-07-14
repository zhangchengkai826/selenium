#pragma once
#include "d3d_app.h"
#include <DirectXCollision.h>

class SeleniumApp : public D3DApp {
public:
	SeleniumApp(HINSTANCE hInstance);
	SeleniumApp(const SeleniumApp &rhs) = delete;
	SeleniumApp& operator=(const SeleniumApp &rhs) = delete;

private:
	DirectX::BoundingSphere mSceneBounds;
};