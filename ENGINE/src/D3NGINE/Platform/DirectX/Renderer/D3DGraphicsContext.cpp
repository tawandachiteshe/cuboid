//
// Created by Jerry on 8/6/2020.
//

#include <d3gpch.h>
#include <SDL_syswm.h>
#include "D3DGraphicsContext.h"
#include <d3d11.h>
#include <SDL_video.h>

namespace D3G
{
    ID3D11Device*            D3DGraphicsContext::m_d3dDevice;
    ID3D11DeviceContext*     D3DGraphicsContext::m_d3dDeviceContext;
    IDXGISwapChain*          D3DGraphicsContext::m_SwapChain;
    ID3D11RenderTargetView*  D3DGraphicsContext::m_mainRenderTargetView;

    void D3DGraphicsContext::Init()
    {
        D3G_CORE_INFO("D3D INIT fn SUCCESS!!!");
        D3D_FEATURE_LEVEL featureLevel;
        const D3D_FEATURE_LEVEL featureLevelArray[2] =
                { D3D_FEATURE_LEVEL_11_0, D3D_FEATURE_LEVEL_10_0 };
        UINT createDeviceFlags = 0;

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
        sd.OutputWindow = m_hwnd;
        D3G_CORE_DEBUG("Hwind status {0}", &m_hwnd == nullptr);
        UINT m4xMsaaQuality = 0;
//        m_d3dDevice->CheckMultisampleQualityLevels(DXGI_FORMAT_R8G8B8A8_UNORM, 4, &m4xMsaaQuality);
        D3G_CORE_INFO("MSAA LEVEL {0}", m4xMsaaQuality);


        sd.SampleDesc.Count = 1;
        sd.SampleDesc.Quality = 0;
        sd.Windowed = TRUE;
        sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;


        bool deviceSuccess = D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, createDeviceFlags, featureLevelArray,
                                      2, D3D11_SDK_VERSION, &sd, &m_SwapChain, &m_d3dDevice, &featureLevel, &m_d3dDeviceContext
                                                           ) != S_OK;
        D3G_CORE_INFO("D3D IS IT COOL {0}", !deviceSuccess);
        D3G_CORE_ASSERT(!deviceSuccess, "Unable to create d3d device and swapchain");

        CreateRenderTarget();
    }

    void D3DGraphicsContext::SwapBuffers()
    {
        m_d3dDeviceContext->OMSetRenderTargets(1, &m_mainRenderTargetView, NULL);
        m_SwapChain->Present(1, 0);
    }


    void D3DGraphicsContext::SetVsync(bool enable)
    {
        //TODO: Tawanda u moron fix this ignorance code
        if(enable)
            m_SwapChain->Present(1, 0);
        else
            m_SwapChain->Present(0, 0);

        D3G_CORE_INFO("Vsync set {0}", true);
    }


    D3DGraphicsContext::D3DGraphicsContext(SDL_Window *window):
    m_Window(window)
    {
        D3G_ASSERT(m_Window, "Window no data");
        SDL_SysWMinfo wmInfo;
        SDL_VERSION(&wmInfo.version);
        SDL_GetWindowWMInfo(m_Window, &wmInfo);
        m_hwnd = (HWND)wmInfo.info.win.window;
        D3G_CORE_INFO("D3D CONTEST INIT SUCCESS!!!");

    }

    void D3DGraphicsContext::CreateRenderTarget()
    {
        ID3D11Texture2D* pBackBuffer;
        m_SwapChain->GetBuffer(0, IID_PPV_ARGS(&pBackBuffer));
        m_d3dDevice->CreateRenderTargetView(pBackBuffer, NULL, &m_mainRenderTargetView);
        D3G_CORE_INFO("Create Render Texture {0}", pBackBuffer == nullptr);
        pBackBuffer->Release();
    }

    D3DGraphicsContext::~D3DGraphicsContext()
    {
        CleanupDeviceD3D();
    }


    void D3DGraphicsContext::CleanupDeviceD3D()
    {
        CleanupRenderTarget();
        if (m_SwapChain) { m_SwapChain->Release(); m_SwapChain = NULL; }
        if (m_d3dDeviceContext) { m_d3dDeviceContext->Release(); m_d3dDeviceContext = NULL; }
        if (m_d3dDevice) { m_d3dDevice->Release(); m_d3dDevice = NULL; }
    }

    void D3DGraphicsContext::CleanupRenderTarget()
    {
        if (m_mainRenderTargetView) { m_mainRenderTargetView->Release(); m_mainRenderTargetView = NULL; }
    }

    void D3DGraphicsContext::ResizeSwapBuffers()
    {
        // Release all outstanding references to the swap chain's buffers before resizing.
        CleanupRenderTarget();
        m_SwapChain->ResizeBuffers(0, 0, 0, DXGI_FORMAT_UNKNOWN, 0);
        CreateRenderTarget();

    }

}