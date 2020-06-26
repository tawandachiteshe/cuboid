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

    void D3DGraphicsContext::Init()
    {
    }

    void D3DGraphicsContext::SwapBuffers(){


    }


    void D3DGraphicsContext::SetVsync(bool enable)
    {

    }


    D3DGraphicsContext::D3DGraphicsContext(SDL_Window *window):
    m_Window(window)
    {

    }

    void D3DGraphicsContext::CreateRenderTarget()
    {
    }

    D3DGraphicsContext::~D3DGraphicsContext()
    {
    }


    void D3DGraphicsContext::CleanupDeviceD3D()
    {
    }

    void D3DGraphicsContext::CleanupRenderTarget()
    {

    }

    void D3DGraphicsContext::ResizeSwapBuffers()
    {

    }

}