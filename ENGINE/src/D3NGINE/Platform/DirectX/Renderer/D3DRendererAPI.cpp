//
// Created by Jerry on 10/6/2020.
//

#include <d3gpch.h>
#include "D3DRendererAPI.h"
#include "D3DGraphicsContext.h"
#include <d3d11.h>
namespace D3G
{

    ID3D11RenderTargetView*  D3DRendererAPI::m_mainRenderTargetView;
    void D3DRendererAPI::Init()
    {


    }

    void D3DRendererAPI::SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
    {

    }

    void D3DRendererAPI::SetClearColor(const glm::vec4 &clearColor)
    {
        m_mainRenderTargetView = D3DGraphicsContext::GetRenderTargetView();
        D3DGraphicsContext::GetContext()->ClearRenderTargetView(m_mainRenderTargetView, (float*)&clearColor);
    }

    void D3DRendererAPI::Clear()
    {
        m_mainRenderTargetView = D3DGraphicsContext::GetRenderTargetView();
        FLOAT DefaultClearColor[4] =  {0.0f, 0.0f, 0.0f, 1.0f};
        D3DGraphicsContext::GetContext()->ClearRenderTargetView(m_mainRenderTargetView, DefaultClearColor);
    }

    void D3DRendererAPI::DrawIndexed(const Ref <VertexArray> &vertexArray, uint32_t indexCount, uint32_t mode)
    {

    }


}