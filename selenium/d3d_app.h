#pragma once
#include <Windows.h>
#include <d3d12.h>

class D3DApp
{
protected:
	D3DApp(HINSTANCE hInstance);

protected:
	static D3DApp* mApp;

	HINSTANCE mhAppInst = nullptr; // application instance handle
};