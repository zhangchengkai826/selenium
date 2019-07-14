#pragma once
#include <Windows.h>
#include <d3d12.h>
#include "timer.h"
#include <wrl/client.h>

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

	// Convenience overrides for handling mouse input.
	virtual void OnMouseDown(WPARAM btnState, int x, int y) { }
	virtual void OnMouseUp(WPARAM btnState, int x, int y) { }
	virtual void OnMouseMove(WPARAM btnState, int x, int y) { }

protected:
	static D3DApp *mApp;

	HINSTANCE mhAppInst = nullptr; // application instance handle
	bool mAppPaused = false;  // is the application paused?
	bool mResizing = false;   // are the resize bars being dragged?
	Timer mTimer;
	Microsoft::WRL::ComPtr<ID3D12Device> md3dDevice;
	int mClientWidth = 800;
	int mClientHeight = 600;

};