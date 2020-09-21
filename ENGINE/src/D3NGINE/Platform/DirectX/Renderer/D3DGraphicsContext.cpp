 //
// Created by Jerry on 8/6/2020.
//

#include <d3gpch.h>
#include <SDL_syswm.h>
#include "D3DGraphicsContext.h"
#include <SDL_video.h>
#include "InitializeD3Devices.h"
#include "D3NGINE/Core/Application.h"

namespace D3G
{

    void D3DGraphicsContext::Init()
    {
       
    }

    void D3DGraphicsContext::SwapBuffers(){

  
        GraphicsEngine()->Present();

    }


    void D3DGraphicsContext::SetVsync(bool enable)
    {
        GraphicsEngine()->SetVSync(enable);
    }


    D3DGraphicsContext::D3DGraphicsContext(HWND window)
    {
        
        const auto& app = Application::Get();

        InitializeD3Devices::Create(window, 1280, 720);

        

    }

    void D3DGraphicsContext::CreateRenderTarget()
    {
    }

    D3DGraphicsContext::~D3DGraphicsContext()
    {

    }


    void D3DGraphicsContext::ResizeSwapBuffers()
    {

    }

}