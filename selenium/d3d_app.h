#pragma once
#include <Windows.h>
#include <d3d12.h>
#include "timer.h"
#include <wrl/client.h>
#include <string>
#include <dxgi1_4.h>

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
	bool InitDirect3D();

	// Convenience overrides for handling mouse input.
	virtual void OnMouseDown(WPARAM btnState, int x, int y) { }
	virtual void OnMouseUp(WPARAM btnState, int x, int y) { }
	virtual void OnMouseMove(WPARAM btnState, int x, int y) { }

protected:
	static D3DApp *mApp;

	HINSTANCE mhAppInst = nullptr; // application instance handle
	HWND mhMainWnd = nullptr; // main window handle
	std::wstring mMainWndCaption = L"Selenium";
	bool mAppPaused = false;  // is the application paused?
	bool mResizing = false;   // are the resize bars being dragged?
	Timer mTimer;
	int mClientWidth = 800;
	int mClientHeight = 600;

	Microsoft::WRL::ComPtr<IDXGIFactory4> mdxgiFactory;
	Microsoft::WRL::ComPtr<ID3D12Device> md3dDevice;
	
	Microsoft::WRL::ComPtr<ID3D12Fence> mFence;
	
	UINT mRtvDescriptorSize = 0;
	UINT mDsvDescriptorSize = 0;
	UINT mCbvSrvUavDescriptorSize = 0;
};