 //
// Created by Jerry on 8/6/2020.
//

#include <Cuboidpch.h>
#include "D3DGraphicsContext.h"
#include "Cuboid/Platform/DirectX/InitializeD3Devices.h"
#include "Cuboid/Core/Application.h"

namespace Cuboid
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
        
        

        InitializeD3Devices::Create(window, 0, 0);

        

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