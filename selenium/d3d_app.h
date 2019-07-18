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
	
	int Run();

	float AspectRatio()const;

protected:
	D3DApp(HINSTANCE hInstance);
	D3DApp(const D3DApp &rhs) = delete;
	D3DApp &operator=(const D3DApp& rhs) = delete;
	
	virtual void Update(const Timer& gt) = 0;
	virtual void Draw(const Timer& gt) = 0;

	D3D12_CPU_DESCRIPTOR_HANDLE DepthStencilView()const;

	virtual void OnResize();

	virtual void CreateRtvAndDsvDescriptorHeaps();

	// Convenience overrides for handling mouse input.
	virtual void OnMouseDown(WPARAM btnState, int x, int y) { }
	virtual void OnMouseUp(WPARAM btnState, int x, int y) { }
	virtual void OnMouseMove(WPARAM btnState, int x, int y) { }

	bool InitMainWindow();
	bool InitDirect3D();

	void CreateCommandObjects();
	void CreateSwapChain();

	void FlushCommandQueue();

	void CalculateFrameStats();

protected:
	static D3DApp *mApp;
	static const int SwapChainBufferCount = 2;

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
	UINT64 mCurrentFence = 0;
	
	UINT mRtvDescriptorSize = 0;
	UINT mDsvDescriptorSize = 0;
	UINT mCbvSrvUavDescriptorSize = 0;

	Microsoft::WRL::ComPtr<ID3D12CommandQueue> mCmdQueue;
	Microsoft::WRL::ComPtr<ID3D12CommandAllocator> mCmdAllocator;
	Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> mCmdList;

	Microsoft::WRL::ComPtr<IDXGISwapChain> mSwapChain;

	DXGI_FORMAT mSwapChainBufferFormat = DXGI_FORMAT_R8G8B8A8_UNORM;
	DXGI_FORMAT mDepthStencilBufferFormat = DXGI_FORMAT_D24_UNORM_S8_UINT;

	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> mRtvHeap;
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> mDsvHeap;

	Microsoft::WRL::ComPtr<ID3D12Resource> mSwapChainBuffer[SwapChainBufferCount];
	int mCurrSwapChainBuffer = 0;
	Microsoft::WRL::ComPtr<ID3D12Resource> mDepthStencilBuffer;

	D3D12_VIEWPORT mScreenViewport;
	D3D12_RECT mScissorRect;
};