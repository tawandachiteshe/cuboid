//
// Created by Jerry on 10/6/2020.
//

#include <d3gpch.h>
#include "D3DRendererAPI.h"
#include "D3DGraphicsContext.h"
#include "InitializeD3Devices.h"

namespace D3G
{

    void D3DRendererAPI::Init()
    {
    }

    void D3DRendererAPI::SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
    {
        D3D11_VIEWPORT vp;
        vp.Width = width;
        vp.Height = height;
        vp.MinDepth = 0.0f;
        vp.MaxDepth = 1.0f;
        vp.TopLeftX = 0;
        vp.TopLeftY = 0;

        GraphicsEngine()->GetContext()->RSSetViewports(1, &vp);
    }

    void D3DRendererAPI::SetClearColor(const glm::vec4 &clearColor)
    {
        GraphicsEngine()->Clear({ clearColor.x, clearColor.y, clearColor.z, clearColor.w});
    }

    void D3DRendererAPI::Clear()
    {

        GraphicsEngine()->Clear({ 0.0f, 0.0f, 0.0f, 1.0f });

    }

    void D3DRendererAPI::DrawIndexed(const Ref <VertexArray> &vertexArray, uint32_t indexCount, uint32_t mode)
    {


    }


}