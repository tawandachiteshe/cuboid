//
// Created by Jerry on 10/6/2020.
//

#include <d3gpch.h>
#include "D3DRendererAPI.h"
#include "D3DGraphicsContext.h"
#include "InitializeD3Devices.h"

namespace D3G
{
    ID3D11BlendState* D3DRendererAPI::m_pBlendState = NULL;

    void D3DRendererAPI::Init()
    {

        {
            D3D11_BLEND_DESC desc;
            ZeroMemory(&desc, sizeof(desc));
            desc.AlphaToCoverageEnable = false;
            desc.RenderTarget[0].BlendEnable = true;
            desc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
            desc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
            desc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
            desc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_INV_SRC_ALPHA;
            desc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
            desc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
            desc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
            GraphicsEngine()->GetDevice()->CreateBlendState(&desc, &m_pBlendState);

            const float blend_factor[4] = { 0.f, 0.f, 0.f, 0.f };
            GraphicsEngine()->GetContext()->OMSetBlendState(m_pBlendState, blend_factor, 0xffffffff);
           
        }

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
        vertexArray->Bind();
        uint32_t count = indexCount ? indexCount : vertexArray->GetIndexBuffer()->GetCount();
        GraphicsEngine()->GetContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
        GraphicsEngine()->GetContext()->DrawIndexed(count, 0, 0);

    }


}