//
// Created by Jerry on 19/6/2020.
//
#include <d3gpch.h>
#include <cstdint>
#include "D3DVertexBuffer.h"
#include "D3DGraphicsContext.h"
#include "D3DShader.h"
#include <d3d11.h>
#include <any>


namespace D3G
{

    D3DVertexBuffer::D3DVertexBuffer(float *vertices, uint32_t size)
    {

        D3D11_BUFFER_DESC desc;
        ZeroMemory(&desc, sizeof(D3D11_BUFFER_DESC));
        desc.Usage = D3D11_USAGE_DEFAULT;
        desc.ByteWidth = size;
        desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
        desc.MiscFlags = 0;
        desc.StructureByteStride = 0;
        desc.CPUAccessFlags = 0;

        D3D11_SUBRESOURCE_DATA pData;
        pData.pSysMem = vertices;
        pData.SysMemPitch = 0;
        pData.SysMemSlicePitch = 0;
        D3G_CORE_INFO( "Vertex buffer status {0}",D3DGraphicsContext::GetDevice()->CreateBuffer(&desc, &pData, &m_VertexBuffer) != S_OK);

    }

    D3DVertexBuffer::D3DVertexBuffer(uint32_t size)
    {


        m_VertexBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
        m_VertexBufferDesc.ByteWidth = size;
        m_VertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
        m_VertexBufferDesc.MiscFlags = 0;
        m_VertexBufferDesc.StructureByteStride = 0;

        D3DGraphicsContext::GetDevice()->CreateBuffer(&m_VertexBufferDesc, nullptr, &m_VertexBuffer);

    }

    D3DVertexBuffer::~D3DVertexBuffer()
    {
        m_VertexBuffer = nullptr;
    }

    void D3G::D3DVertexBuffer::Bind() const
    {
        UINT offset = 0;
        UINT stride = m_Layout.GetStride();
        D3DGraphicsContext::GetContext()->IASetVertexBuffers(0, 1, &m_VertexBuffer, &stride, &offset);
    }

    void D3G::D3DVertexBuffer::UnBind() const
    {

    }

    void D3G::D3DVertexBuffer::SetLayout(const BufferLayout &layout)
    {

        m_Layout = layout;

    }

    void D3G::D3DVertexBuffer::SetData(const void *data, uint32_t size)
    {


        D3D11_MAPPED_SUBRESOURCE mapped_res;
        D3DGraphicsContext::GetContext()->Map(m_VertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mapped_res);

        void* LocalData = mapped_res.pData;
        memcpy(LocalData, data, size);

        D3DGraphicsContext::GetContext()->Unmap(m_VertexBuffer, 0);

    }

    const BufferLayout& D3G::D3DVertexBuffer::GetBufferLayout() const
    {
        return m_Layout;
    }

    void D3DVertexBuffer::CreateVertexBufferNow()
    {

    }

}