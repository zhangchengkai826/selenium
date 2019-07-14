#include "d3d_app.h"
#include <cassert>

D3DApp* D3DApp::mApp = nullptr;

D3DApp::D3DApp(HINSTANCE hInstance)
	: mhAppInst(hInstance)
{
	// Only one D3DApp can be constructed.
	assert(mApp == nullptr);
	mApp = this;
}