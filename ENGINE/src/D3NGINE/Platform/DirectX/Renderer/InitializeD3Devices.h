#pragma once

#include <d3d11.h>

#include "D3NGINE/Core/Core.h"


#include "DxHelper.h"

class InitializeD3Devices
{
protected:
	static ID3D11Device*			m_pDevice;
	static ID3D11Texture2D*			m_pBackBuffer;
	static ID3D11Texture2D*			m_pDepthStencilBuffer;
	static ID3D11RenderTargetView*	m_pRenderTargetView;
	static IDXGISwapChain*			m_pSwapChain;
	static RECT						m_rcScreenRect;
	static ID3D11InfoQueue*			m_pMessageQueue;
	static ID3D11DepthStencilView*  m_pDepthStencilView;
	static ID3D11DepthStencilState* m_pDepthStencilState;
	static ID3D11DeviceContext*		m_pDeviceContext;


	bool m_bEnableVsync { true };

public:
	InitializeD3Devices() = default;
	void CreateRenderTarget();
	void CleanupDeviceD3D();
	void CleanupRenderTarget();

private:
	static D3G::Ref<InitializeD3Devices> initDevices;

public:

	void CreateDepthStencilBuffer();

	void DestroyAll();
	~InitializeD3Devices();

	void InitD3D(HWND hwnd,int width, int height, int bpp);

	void DumpMessages();

	IDXGISwapChain* GetSwapChain() { return m_pSwapChain; }

	ID3D11Device* GetDevice() 
	{

		return m_pDevice;

	}

	ID3D11Texture2D* GetBackBuffer()
	{
		return m_pBackBuffer;
	}

	ID3D11DeviceContext* GetContext() { return m_pDeviceContext; }



	int Width() const
	{
		return m_rcScreenRect.right;
	}

	int Height() const
	{
		return m_rcScreenRect.bottom;
	}

	void Present();

	void Clear(const float(&colClear)[4]);

	static D3G::Ref<InitializeD3Devices> GetDevices()
	{
		return initDevices;
	}

	void SetVSync(bool enabled) { m_bEnableVsync = enabled; }
	
	static void Create(HWND hWnd, short width, short height); 

};

inline D3G::Ref<InitializeD3Devices> GraphicsEngine()
{
	return InitializeD3Devices::GetDevices();
}

