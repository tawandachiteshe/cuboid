//
// Created by Jerry on 19/6/2020.
//

#include "D3DIndexBuffer.h"
#include "D3DGraphicsContext.h"
#include "InitializeD3Devices.h" 

namespace Cuboid
{

    void D3DIndexBuffer::Bind() const
    {

        GraphicsEngine()->GetContext()->IASetIndexBuffer(m_pIndexBuffer, DXGI_FORMAT_R32_UINT, 0u);
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

    }

    D3DIndexBuffer::D3DIndexBuffer(uint32_t *indices, uint32_t count) :
        m_Count(count)
    {
        HRESULT r = S_OK;
        D3D11_BUFFER_DESC buff_desc = {};
        buff_desc.Usage = D3D11_USAGE_DEFAULT;
        buff_desc.ByteWidth = sizeof(uint32_t) * count;
        buff_desc.BindFlags = D3D11_BIND_INDEX_BUFFER;
        buff_desc.CPUAccessFlags = 0u;

        D3D11_SUBRESOURCE_DATA indexBufferData = {};
        indexBufferData.pSysMem = indices;

        if (FAILED(r = GraphicsEngine()->GetDevice()->CreateBuffer(&buff_desc, &indexBufferData, &m_pIndexBuffer)))
        {
            CUBOID_CORE_ERROR("D3d failed to Creating Index buffer");
        }

    }

}
