//
// Created by Jerry on 10/6/2020.
//

#include <Cuboidpch.h>
#include "D3DRendererAPI.h"
#include "D3DGraphicsContext.h"
#include "InitializeD3Devices.h"

namespace Cuboid
{
    ID3D11BlendState* D3DRendererAPI::m_pBlendState = NULL;
    ID3D11RasterizerState* D3DRendererAPI::m_pRasterizerState = NULL;

    //TODO: clean here...

    void D3DRendererAPI::Init()
    {
        HRESULT hr = S_OK;
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

            //TODO make blend state flexible...
            //GraphicsEngine()->GetContext()->OMSetBlendState(m_pBlendState, blend_factor, 0xffffffff);
           
        }

        {
            D3D11_RASTERIZER_DESC desc;
            ZeroMemory(&desc, sizeof(desc));
            desc.FillMode = D3D11_FILL_SOLID;
            desc.CullMode = D3D11_CULL_NONE;
            desc.ScissorEnable = false;
            desc.DepthClipEnable = false;
            desc.FrontCounterClockwise = true;
            hr = GraphicsEngine()->GetDevice()->CreateRasterizerState(&desc, &m_pRasterizerState);
        }

        //

    }

    void D3DRendererAPI::SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
    {
        D3D11_VIEWPORT vp;
        vp.Width = (FLOAT)width;
        vp.Height = (FLOAT)height;
        vp.MinDepth = 0.0f;
        vp.MaxDepth = 1.0f;
        vp.TopLeftX = 0.0f;
        vp.TopLeftY = 0.0f;

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

        GraphicsEngine()->GetContext()->RSSetState(m_pRasterizerState);
        GraphicsEngine()->GetContext()->DrawIndexed(count, 0, 0);

    }


}