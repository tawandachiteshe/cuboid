//
// Created by Jerry on 19/6/2020.
//

#include "D3DIndexBuffer.h"
#include "D3DGraphicsContext.h"
#include <d3d11.h>

namespace D3G
{

    void D3DIndexBuffer::Bind() const
    {
        //TODO: Support 16 bit indices to save memory Tawanda
        D3DGraphicsContext::GetContext()->IASetIndexBuffer(m_IndexBuffer, DXGI_FORMAT_R32_UINT, 0);


    }

    void D3DIndexBuffer::UnBind() const
    {

    }

    uint32_t D3DIndexBuffer::GetCount() const
    {
        return m_Count;
    }

    D3DIndexBuffer::~D3DIndexBuffer()
    {

        m_IndexBuffer = nullptr;

    }

    D3DIndexBuffer::D3DIndexBuffer(uint32_t *indices, uint32_t count)
    {

        m_Count = count;
        D3D11_BUFFER_DESC indexBufferDesc;

        indexBufferDesc.Usage = D3D11_USAGE_IMMUTABLE;
        indexBufferDesc.ByteWidth = sizeof(UINT) * count;
        indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
        indexBufferDesc.CPUAccessFlags = 0;
        indexBufferDesc.MiscFlags = 0;
        indexBufferDesc.StructureByteStride = 0;

        D3D11_SUBRESOURCE_DATA indicesData;
        indicesData.pSysMem = indices;

        D3G_CORE_INFO("Index Buffer creation {0}",
                      D3DGraphicsContext::GetDevice()->CreateBuffer(&indexBufferDesc, &indicesData, &m_IndexBuffer) != S_OK);

    }

}
