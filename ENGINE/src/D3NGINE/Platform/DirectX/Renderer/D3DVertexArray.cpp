//
// Created by Jerry on 19/6/2020.
//

#include <d3gpch.h>
#include "D3DVertexArray.h"
#include "D3DGraphicsContext.h"
#include "D3DShader.h"
#include "D3DVertexBuffer.h"

#include <d3d11.h>

namespace D3G
{

    void D3DVertexArray::Bind() const
    {

        m_IdxBuffer->Bind();

    }

    void D3DVertexArray::UnBind() const
    {

    }

    const Ref <IndexBuffer>& D3DVertexArray::GetIndexBuffer() const
    {
        return m_IdxBuffer;
    }

    void D3DVertexArray::AddVertexBuffer(const Ref <VertexBuffer>& vtxBuffer) const
    {
        
    }

    void D3DVertexArray::AddVertexBuffer(const D3G::Ref<D3G::VertexBuffer> &vtxBuffer)
    {
        vtxBuffer->Bind();
    }

    void D3DVertexArray::SetIndexBuffer(const Ref <IndexBuffer>& idxBuffer)
    {

        m_IdxBuffer = idxBuffer;
    }

    D3DVertexArray::D3DVertexArray()
    {

    }

    D3DVertexArray::~D3DVertexArray()
    {

    }

    void D3DVertexArray::SetShader(const Ref<Shader>& mShader)
    {

    }
}