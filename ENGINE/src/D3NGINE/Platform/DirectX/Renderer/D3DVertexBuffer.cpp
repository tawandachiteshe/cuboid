//
// Created by Jerry on 19/6/2020.
//

#include <cstdint>
#include "D3DVertexBuffer.h"
#include "D3DGraphicsContext.h"
#include <d3d11.h>

namespace D3G
{
    D3DVertexBuffer::D3DVertexBuffer(float *vertices, uint32_t size)
    {
        D3D11_BUFFER_DESC vertexBufferDesc;
        vertexBufferDesc.Usage = D3D11_USAGE_IMMUTABLE;
        vertexBufferDesc.ByteWidth = size;
        vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
        vertexBufferDesc.MiscFlags = 0;
        vertexBufferDesc.StructureByteStride = 0;

        D3D11_SUBRESOURCE_DATA verticesData;
        verticesData.pSysMem = vertices;

        D3DGraphicsContext::GetDevice()->CreateBuffer(&vertexBufferDesc, &verticesData, &m_VertexBuffer);
    }

    D3DVertexBuffer::D3DVertexBuffer(uint32_t size)
    {

        D3D11_BUFFER_DESC vertexBufferDesc;
        vertexBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
        vertexBufferDesc.ByteWidth = size;
        vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
        vertexBufferDesc.MiscFlags = 0;
        vertexBufferDesc.StructureByteStride = 0;

        D3DGraphicsContext::GetDevice()->CreateBuffer(&vertexBufferDesc, nullptr, &m_VertexBuffer);
    }

    D3DVertexBuffer::~D3DVertexBuffer()
    {
        m_VertexBuffer = nullptr;
    }

    void D3G::D3DVertexBuffer::Bind() const
    {
        UINT offset = 0;
        UINT stride = m_Layout.GetStride();
        D3DGraphicsContext::GetContext()->IASetVertexBuffers(0, 1, &m_VertexBuffer, (const UINT*)offset, (const UINT*)stride);
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

}