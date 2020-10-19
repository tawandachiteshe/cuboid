#include "Cuboidpch.h"
#include "InitializeD3Devices.h"


namespace Cuboid
{

	Cuboid::Ref<InitializeD3Devices> InitializeD3Devices::initDevices = nullptr;

	InitializeD3Devices::ComPtr<ID3D11Device>				InitializeD3Devices::m_pDevice;
	InitializeD3Devices::ComPtr<ID3D11RenderTargetView>		InitializeD3Devices::m_pRenderTargetView;
	InitializeD3Devices::ComPtr<IDXGISwapChain>				InitializeD3Devices::m_pSwapChain;
	InitializeD3Devices::ComPtr<ID3D11DeviceContext>		InitializeD3Devices::m_pDeviceContext;
	InitializeD3Devices::ComPtr<ID3D11Texture2D>			InitializeD3Devices::m_pBackBuffer;

	void InitializeD3Devices::DestroyAll()
	{

		SafeRelease(m_pRenderTargetView);
		SafeRelease(m_pSwapChain);
		SafeRelease(m_pDevice);

		initDevices = NULL;

	}

	InitializeD3Devices::~InitializeD3Devices()
	{
		DestroyAll();
	}

	void InitializeD3Devices::InitD3D(HWND hwnd, uint32_t width, uint32_t height, uint32_t bpp)
	{
		HRESULT r = S_OK;

		DXGI_SWAP_CHAIN_DESC sd;
		ZeroMemory(&sd, sizeof(sd));
		sd.BufferCount = 2;
		sd.BufferDesc.Width = width;
		sd.BufferDesc.Height = height;
		sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		sd.BufferDesc.RefreshRate.Numerator = 60;
		sd.BufferDesc.RefreshRate.Denominator = 1;
		sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
		sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT | DXGI_USAGE_SHADER_INPUT;
		sd.OutputWindow = hwnd;
		sd.SampleDesc.Count = 1;
		sd.SampleDesc.Quality = 0;
		sd.Windowed = TRUE;
		sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;


		UINT createDeviceFlags = 0;
		D3D_FEATURE_LEVEL featureLevel;
		const D3D_FEATURE_LEVEL featureLevelArray[2] = { D3D_FEATURE_LEVEL_11_0, D3D_FEATURE_LEVEL_10_0, };
		r = D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, createDeviceFlags, featureLevelArray, 2, D3D11_SDK_VERSION, &sd, m_pSwapChain.GetAddressOf(), m_pDevice.GetAddressOf(), &featureLevel, m_pDeviceContext.GetAddressOf());

		if (r != S_OK)
		{
			CUBOID_CORE_ERROR("Could not create IDirect3DDevice11");
		}



		CreateRenderTarget();

	}

	void InitializeD3Devices::CleanupRenderTarget()
	{
		if (m_pRenderTargetView) { m_pRenderTargetView->Release(); }
		if (m_pBackBuffer) { m_pBackBuffer->Release(); }
	}


	void InitializeD3Devices::CleanupDeviceD3D()
	{
		CleanupRenderTarget();
		if (m_pSwapChain) { m_pSwapChain->Release(); }
		if (m_pDevice) { m_pDevice->Release(); }
	}

	void InitializeD3Devices::CreateRenderTarget()
	{
		HRESULT r = S_OK;
		r = m_pSwapChain->GetBuffer(0, IID_PPV_ARGS(m_pBackBuffer.GetAddressOf()));

		if (FAILED(r))
		{
			CUBOID_CORE_CRITICAL("Could not get back buffer");
		}


		r = m_pDevice->CreateRenderTargetView(m_pBackBuffer.Get(), NULL, m_pRenderTargetView.GetAddressOf());

		if (FAILED(r))
		{
			CUBOID_CORE_CRITICAL("Could not create render target view");
		}
	}



	void InitializeD3Devices::Present()
	{

		HRESULT r = S_OK;

		CUBOID_CORE_ASSERT(m_pDevice, "can't present a buffer without a device");

		if (m_bEnableVsync)
			r = m_pSwapChain->Present(1, 0);
		else
			r = m_pSwapChain->Present(0, 0);

		if (FAILED(r))
		{
			CUBOID_CORE_ERROR("Present Failed!!!");
		}

	}


	void InitializeD3Devices::Clear(const float(&colClear)[4])
	{

		HRESULT r = S_OK;

		CUBOID_CORE_ASSERT(m_pDeviceContext, "Cannot clear without d3d device context");
		m_pDeviceContext->ClearRenderTargetView(m_pRenderTargetView.Get(), colClear);
		m_pDeviceContext->OMSetRenderTargets(1, m_pRenderTargetView.GetAddressOf(), NULL);

	}



	void InitializeD3Devices::Create(HWND hWnd, uint32_t width, uint32_t height)
	{
		GraphicsEngine()->InitD3D(hWnd, width, height, 32);
		initDevices = Cuboid::CreateRef<InitializeD3Devices>();

	}


}