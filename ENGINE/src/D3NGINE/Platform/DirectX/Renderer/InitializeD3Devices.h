#pragma once

#include <d3d10_1.h>
#include <d3d10.h>

#include "D3NGINE/Core/Core.h"


#include "DxHelper.h"

class InitializeD3Devices
{
protected:
	static ID3D10Device*			m_pDevice;
	static ID3D10Texture2D*			m_pBackBuffer;
	static ID3D10RenderTargetView*	m_pRenderTargetView;
	static IDXGISwapChain*			m_pSwapChain;
	static RECT						m_rcScreenRect;
	static ID3D10InfoQueue*			m_pMessageQueue;
	bool m_bEnableVsync { true };

public:
	InitializeD3Devices() = default;

private:
	static D3G::Ref<InitializeD3Devices> initDevices;

public:

	void DestroyAll();
	~InitializeD3Devices();

	void InitD3D(HWND hwnd,int width, int height, int bpp);

	void DumpMessages();

	ID3D10Device* GetDevice() 
	{

		return m_pDevice;

	}

	ID3D10Texture2D* GetBackBuffer()
	{
		return m_pBackBuffer;
	}


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

inline D3G::Ref<InitializeD3Devices> Graphics()
{
	return InitializeD3Devices::GetDevices();
}

