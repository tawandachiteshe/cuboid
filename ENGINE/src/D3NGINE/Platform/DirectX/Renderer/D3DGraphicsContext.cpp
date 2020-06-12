//
// Created by Jerry on 8/6/2020.
//

#include <d3gpch.h>
#include "D3DGraphicsContext.h"

namespace D3G
{
    ID3D11Device*            D3DGraphicsContext::m_d3dDevice;
    ID3D11DeviceContext*     D3DGraphicsContext::m_d3dDeviceContext;
    IDXGISwapChain*          D3DGraphicsContext::m_SwapChain;
    ID3D11RenderTargetView*  D3DGraphicsContext::m_mainRenderTargetView;

    void D3DGraphicsContext::Init()
    {
        D3D_FEATURE_LEVEL featureLevel;
        const D3D_FEATURE_LEVEL featureLevelArray[4] =
                { D3D_FEATURE_LEVEL_11_0, D3D_FEATURE_LEVEL_10_1, D3D_FEATURE_LEVEL_10_0, D3D_FEATURE_LEVEL_9_3};
        UINT createDeviceFlags = 0;

        DXGI_SWAP_CHAIN_DESC sd;
        sd.BufferCount = 2;
        sd.BufferDesc.Width = 0;
        sd.BufferDesc.Height = 0;
        sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
        sd.BufferDesc.RefreshRate.Numerator = 60;
        sd.BufferDesc.RefreshRate.Denominator = 1;
        sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
        sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
        sd.OutputWindow = *m_hwnd;

        UINT m4xMsaaQuality;
        m_d3dDevice->CheckMultisampleQualityLevels(DXGI_FORMAT_R8G8B8A8_UNORM, 4, &m4xMsaaQuality);
        D3G_CORE_INFO("MSAA LEVEL {0}", m4xMsaaQuality);

        if(m4xMsaaQuality) {

            sd.SampleDesc.Count = 1;
            sd.SampleDesc.Quality = 0;

        }else {

            sd.SampleDesc.Count = 4;
            sd.SampleDesc.Quality = m4xMsaaQuality - 1;
        }
        sd.Windowed = TRUE;
        sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;


        bool deviceSuccess = D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, createDeviceFlags, featureLevelArray,
                                      2, D3D11_SDK_VERSION, &sd, &m_SwapChain,
                                                           &m_d3dDevice, &featureLevel, &m_d3dDeviceContext) != S_OK;
        D3G_CORE_ASSERT(deviceSuccess, "Unable to create d3d device and swapchain");
    }

    void D3DGraphicsContext::SwapBuffers()
    {

    }

    void D3DGraphicsContext::CreateRenderTarget()
    {
        ID3D11Texture2D* pBackBuffer;
        m_SwapChain->GetBuffer(0, IID_PPV_ARGS(&pBackBuffer));
        m_d3dDevice->CreateRenderTargetView(pBackBuffer, NULL, &m_mainRenderTargetView);
        pBackBuffer->Release();
    }

    void D3DGraphicsContext::SetVsync(bool enable)
    {
        if(enable)
            m_SwapChain->Present(1, 0);
        else
            m_SwapChain->Present(0, 0);
    }

    void D3DGraphicsContext::Set_hwnd(const HWND *hwnd)
    {
        m_hwnd = hwnd;
    }
}