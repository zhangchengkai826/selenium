#pragma once
#include "d3d_app.h"
#include <DirectXCollision.h>

class SeleniumApp : public D3DApp {
public:
	SeleniumApp(HINSTANCE hInstance);

private:
	DirectX::BoundingSphere mSceneBounds;
};