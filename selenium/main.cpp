#include <Windows.h>
#include <crtdbg.h>
#include "selenium_app.h"
#include "d3d_util.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE prevInstance,
	PSTR cmdLine, int showCmd)
{
	// Enable run-time memory check for debug builds.
#if defined(DEBUG) | defined(_DEBUG)
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif
	try
	{
		SeleniumApp app(hInstance);
		if (!app.Initialize())
			return 0;
		return app.Run();
	}
	catch (D3DException &e)
	{
		MessageBox(nullptr, e.ToString().c_str(), L"Error", MB_OK);
		return 0;
	}
}