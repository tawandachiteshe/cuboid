#include "d3gpch.h"
#include "InitializeD3Devices.h"


D3G::Ref<InitializeD3Devices> InitializeD3Devices::initDevices = nullptr;

ID3D11Device*			 InitializeD3Devices::m_pDevice				= nullptr;
ID3D11Texture2D*		 InitializeD3Devices::m_pBackBuffer			= nullptr;
ID3D11Texture2D*		 InitializeD3Devices::m_pDepthStencilBuffer  = nullptr;
ID3D11RenderTargetView*  InitializeD3Devices::m_pRenderTargetView	= nullptr;
IDXGISwapChain*			 InitializeD3Devices::m_pSwapChain			= nullptr;
ID3D11InfoQueue*		 InitializeD3Devices::m_pMessageQueue		= nullptr;
RECT					 InitializeD3Devices::m_rcScreenRect			= {};
ID3D11DepthStencilView*  InitializeD3Devices::m_pDepthStencilView	= nullptr;
ID3D11DepthStencilState* InitializeD3Devices::m_pDepthStencilState  = nullptr;
ID3D11DeviceContext*	 InitializeD3Devices::m_pDeviceContext		= nullptr;


void InitializeD3Devices::DestroyAll()
{

	if(m_pMessageQueue)
		SafeRelease(m_pMessageQueue);

	SafeRelease(m_pRenderTargetView);
	SafeRelease(m_pBackBuffer);
	SafeRelease(m_pSwapChain);
	SafeRelease(m_pDevice);

	initDevices = NULL;

}

InitializeD3Devices::~InitializeD3Devices()
{
	DestroyAll();
}

void InitializeD3Devices::InitD3D(HWND hwnd, int width, int height, int bpp)
{
	HRESULT r = S_OK;

	DXGI_SWAP_CHAIN_DESC sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.BufferCount = 2;
	sd.BufferDesc.Width = 0;
	sd.BufferDesc.Height = 0;
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	sd.BufferDesc.RefreshRate.Numerator = 60;
	sd.BufferDesc.RefreshRate.Denominator = 1;
	sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.OutputWindow = hwnd;
	sd.SampleDesc.Count = 1;
	sd.SampleDesc.Quality = 0;
	sd.Windowed = TRUE;
	sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	

	UINT createDeviceFlags = 0;
	D3D_FEATURE_LEVEL featureLevel;
	const D3D_FEATURE_LEVEL featureLevelArray[2] = { D3D_FEATURE_LEVEL_11_0, D3D_FEATURE_LEVEL_10_0, };
	r = D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, createDeviceFlags, featureLevelArray, 2, D3D11_SDK_VERSION, &sd, &m_pSwapChain, &m_pDevice, &featureLevel, &m_pDeviceContext);

	if (r != S_OK)
	{
		D3G_CORE_ERROR("Could not create IDirect3DDevice10");
	}

	/*
	r = m_pDevice->QueryInterface(
		__uuidof(ID3D10InfoQueue), (LPVOID*)&m_pMessageQueue);
	if (FAILED(r))
	{
		D3G_CORE_CRITICAL("Could not create IDirect3DDevice10 message queue");
	}
	m_pMessageQueue->SetMuteDebugOutput(false); // No muting
	m_pMessageQueue->SetMessageCountLimit(-1); // Unlimited messages
	*/

	m_rcScreenRect.left = m_rcScreenRect.top = 0;
	m_rcScreenRect.right = width;
	m_rcScreenRect.bottom = height;


	CreateRenderTarget();
	

	m_pDeviceContext->OMSetRenderTargets(1, &m_pRenderTargetView, NULL);

	D3D11_VIEWPORT vp;
	vp.Width = (FLOAT)width;
	vp.Height = (FLOAT)height;
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
	m_pDeviceContext->RSSetViewports(1, &vp);

}

void InitializeD3Devices::CleanupRenderTarget()
{
	if (m_pRenderTargetView) { m_pRenderTargetView->Release(); m_pRenderTargetView = NULL; }
}

void InitializeD3Devices::CleanupDeviceD3D()
{
	CleanupRenderTarget();
	if (m_pSwapChain) { m_pSwapChain->Release(); m_pSwapChain = NULL; }
	if (m_pDevice) { m_pDevice->Release(); m_pDevice = NULL; }
}

void InitializeD3Devices::CreateRenderTarget()
{
	HRESULT r = S_OK;

	r = m_pSwapChain->GetBuffer(0, IID_PPV_ARGS(&m_pBackBuffer));

	if (FAILED(r))
	{
		D3G_CORE_CRITICAL("Could not get back buffer");
	}

	r = m_pDevice->CreateRenderTargetView(m_pBackBuffer, NULL, &m_pRenderTargetView);

	if (FAILED(r))
	{
		D3G_CORE_CRITICAL("Could not create render target view");
	}
}

void InitializeD3Devices::DumpMessages()
{
#if 0
	D3G_CORE_ASSERT(m_pMessageQueue, "Message queue not yet created!!!!");

	HRESULT r = 0;

	while(true)
	{

		SIZE_T messageLength = 0;

		r = m_pMessageQueue->GetMessage(0, NULL, &messageLength);

		if (messageLength == 0)
			break;

		D3D10_MESSAGE* pMessage = (D3D10_MESSAGE*)malloc(messageLength);

		r = m_pMessageQueue->GetMessage(0, pMessage, &messageLength);
		if (FAILED(r))
		{
			D3G_CORE_ERROR("Failed to get Direct3D Message");
			break;
		}


		D3G_CORE_ERROR("D3DDMSG [Cat[%i] Sev[%i] ID[%i]: %s\n",
			pMessage->Category, pMessage->Severity,
			pMessage->ID, pMessage->pDsescription);

	}
#endif

}

void InitializeD3Devices::Present()
{

	HRESULT r = S_OK;

	D3G_CORE_ASSERT(m_pDevice, "can't present a buffer without a device");

	if(m_bEnableVsync)
		r = m_pSwapChain->Present(1, 0);
	else
		r = m_pSwapChain->Present(1, 0);

	if(FAILED(r))
	{
		D3G_CORE_ERROR("Present Failed!!!");
	}

	//DumpMessages();
}

void  InitializeD3Devices::CreateDepthStencilBuffer() 
{
	HRESULT r = 0;
	// Create the depth buffer
	D3D11_TEXTURE2D_DESC descDepth;
	ZeroMemory(&descDepth, sizeof(descDepth));
	descDepth.Width = m_rcScreenRect.right;
	descDepth.Height = m_rcScreenRect.bottom;
	descDepth.MipLevels = 1;
	descDepth.ArraySize = 1;

	descDepth.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	descDepth.SampleDesc.Count = 1;
	descDepth.SampleDesc.Quality = 0;
	descDepth.Usage = D3D11_USAGE_DEFAULT;
	descDepth.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	descDepth.CPUAccessFlags = 0;
	descDepth.MiscFlags = 0;
	r = m_pDevice->CreateTexture2D(&descDepth, NULL, &m_pDepthStencilBuffer);

	if (FAILED(r))
	{
		D3G_CORE_ERROR("Unable to create depth buffer");
	}

	D3D11_DEPTH_STENCIL_DESC descDS;
	ZeroMemory(&descDS, sizeof(descDS));
	descDS.DepthEnable = true;
	descDS.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	descDS.DepthFunc = D3D11_COMPARISON_LESS;
	// Stencil test values
	descDS.StencilEnable = true;
	descDS.StencilReadMask = (UINT8)0xFFFFFFFF;
	descDS.StencilWriteMask = (UINT8)0xFFFFFFFF;
	// Stencil op if pixel is front
	descDS.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	descDS.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
	descDS.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	descDS.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
	// Stencil op if pixel is back
	descDS.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	descDS.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
	descDS.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	descDS.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

	r = m_pDevice->CreateDepthStencilState(&descDS, &m_pDepthStencilState);
	if (FAILED(r))
	{
		D3G_CORE_ERROR("Could not create depth/stencil state");
	}
	m_pDeviceContext->OMSetDepthStencilState(m_pDepthStencilState, 1);

	D3D11_DEPTH_STENCIL_VIEW_DESC descDSView;
	ZeroMemory(&descDSView, sizeof(descDSView));
	descDSView.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	descDSView.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	descDSView.Texture2D.MipSlice = 0;

	r = m_pDevice->CreateDepthStencilView(
		m_pDepthStencilBuffer, &descDSView, &m_pDepthStencilView);
	if (FAILED(r))
	{
		D3G_CORE_ERROR("Could not create depth/stencil view");
	}
}

void InitializeD3Devices::Clear(const float(&colClear)[4])
{

	HRESULT r = S_OK;

	D3G_CORE_ASSERT(m_pDeviceContext, "Cannot clear without d3d device context");

	m_pDeviceContext->OMSetRenderTargets(1, &m_pRenderTargetView, NULL);
	m_pDeviceContext->ClearRenderTargetView(m_pRenderTargetView, colClear);

}

void InitializeD3Devices::Create(HWND hWnd, short width, short height)
{
	GraphicsEngine()->InitD3D(hWnd, width, height, 32);
	initDevices = D3G::CreateRef<InitializeD3Devices>();
	

	
}
