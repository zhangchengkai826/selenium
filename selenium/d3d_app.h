#pragma once
#include <Windows.h>
#include <d3d12.h>
#include "timer.h"

class D3DApp
{
public:
	static D3DApp *GetApp();

	virtual LRESULT MsgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
	virtual bool Initialize();

protected:
	D3DApp(HINSTANCE hInstance);
	D3DApp(const D3DApp &rhs) = delete;
	D3DApp &operator=(const D3DApp& rhs) = delete;

	bool InitMainWindow();

protected:
	static D3DApp *mApp;

	HINSTANCE mhAppInst = nullptr; // application instance handle
	bool      mAppPaused = false;  // is the application paused?
	Timer mTimer;
};