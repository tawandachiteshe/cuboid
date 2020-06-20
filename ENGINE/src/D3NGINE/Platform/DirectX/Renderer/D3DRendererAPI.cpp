//
// Created by Jerry on 10/6/2020.
//

#include <d3gpch.h>
#include "D3DRendererAPI.h"
#include "D3DGraphicsContext.h"
#include <d3d11.h>

namespace D3G
{
    struct D3DRendererAPIData {

        ID3D11RasterizerState*      m_RasterizerState = NULL;
        ID3D11BlendState*           m_BlendState = NULL;
        ID3D11DepthStencilState*    m_DepthStencilState = NULL;


        ~D3DRendererAPIData()
        {
            if(m_RasterizerState)
                m_RasterizerState = nullptr;

            if(m_BlendState)
                m_BlendState = nullptr;

            if(m_DepthStencilState)
                m_DepthStencilState = nullptr;
        }

    };

    ID3D11RenderTargetView*  D3DRendererAPI::m_mainRenderTargetView;
    static D3DRendererAPIData s_RendererData;

    void D3DRendererAPI::Init()
    {


        D3D11_BLEND_DESC BlendDesc;
        ZeroMemory(&BlendDesc, sizeof(BlendDesc));
        BlendDesc.AlphaToCoverageEnable = false;
        BlendDesc.RenderTarget[0].BlendEnable = true;
        BlendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
        BlendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
        BlendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
        BlendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_INV_SRC_ALPHA;
        BlendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
        BlendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
        BlendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
        D3DGraphicsContext::GetDevice()->CreateBlendState(&BlendDesc, &s_RendererData.m_BlendState);


        // Create the rasterizer state
        D3D11_RASTERIZER_DESC RasterizerDesc;
        ZeroMemory(&RasterizerDesc, sizeof(RasterizerDesc));
        RasterizerDesc.FillMode = D3D11_FILL_SOLID;
        RasterizerDesc.CullMode = D3D11_CULL_NONE;
        RasterizerDesc.ScissorEnable = true;
        RasterizerDesc.DepthClipEnable = true;

        D3DGraphicsContext::GetDevice()->CreateRasterizerState(&RasterizerDesc, &s_RendererData.m_RasterizerState);



        D3D11_DEPTH_STENCIL_DESC DepthStencilDesc;
        ZeroMemory(&DepthStencilDesc, sizeof(DepthStencilDesc));
        DepthStencilDesc.DepthEnable = false;
        DepthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
        DepthStencilDesc.DepthFunc = D3D11_COMPARISON_ALWAYS;
        DepthStencilDesc.StencilEnable = false;
        DepthStencilDesc.FrontFace.StencilFailOp = DepthStencilDesc.FrontFace.StencilDepthFailOp = DepthStencilDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
        DepthStencilDesc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
        DepthStencilDesc.BackFace = DepthStencilDesc.FrontFace;
        D3DGraphicsContext::GetDevice()->CreateDepthStencilState(&DepthStencilDesc, &s_RendererData.m_DepthStencilState);


        D3DGraphicsContext::GetContext()->OMSetDepthStencilState(s_RendererData.m_DepthStencilState, 0);

        const float blend_factor[4] = { 0.f, 0.f, 0.f, 0.f };
        D3DGraphicsContext::GetContext()->OMSetBlendState(s_RendererData.m_BlendState, blend_factor, 0xffffffff);
        D3DGraphicsContext::GetContext()->RSSetState(s_RendererData.m_RasterizerState);
    }

    void D3DRendererAPI::SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
    {

        D3D11_VIEWPORT vp;
        memset(&vp, 0, sizeof(D3D11_VIEWPORT));
        vp.Width = (FLOAT)width;
        vp.Height = (FLOAT)height;
        vp.MinDepth = 0.0f;
        vp.MaxDepth = 1.0f;
        vp.TopLeftX = (FLOAT)x;
        vp.TopLeftY = (FLOAT)y;

        D3DGraphicsContext::GetContext()->RSSetViewports(1, &vp);

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
        vertexArray->Bind();
        uint32_t count = indexCount ? indexCount : vertexArray->GetIndexBuffer()->GetCount();

        D3DGraphicsContext::GetContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
        D3DGraphicsContext::GetContext()->DrawIndexed(count, 0, 0);

    }


}