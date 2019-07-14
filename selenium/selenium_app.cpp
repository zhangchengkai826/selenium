#include "selenium_app.h"
#include <DirectXMath.h>

using namespace DirectX;

SeleniumApp::SeleniumApp(HINSTANCE hInstance)
	: D3DApp(hInstance)
{
	// Estimate the scene bounding sphere manually since we know how the scene was constructed.
	// The grid is the "widest object" with a width of 20 and depth of 30.0f, and centered at
	// the world space origin.  In general, you need to loop over every world space vertex
	// position and compute the bounding sphere.
	mSceneBounds.Center = XMFLOAT3(0.0f, 0.0f, 0.0f);
	mSceneBounds.Radius = sqrtf(10.0f*10.0f + 15.0f*15.0f);
}

bool SeleniumApp::Initialize()
{
	if (!D3DApp::Initialize())
		return false;
	return true;
}