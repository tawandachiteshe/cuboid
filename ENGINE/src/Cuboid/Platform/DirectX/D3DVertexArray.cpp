//
// Created by Jerry on 19/6/2020.
//

#include <Cuboidpch.h>
#include "D3DVertexArray.h"
#include "Cuboid/Platform/DirectX/InitializeD3Devices.h"
#include "D3DShader.h"
#include "D3DVertexBuffer.h"

#include <d3d11.h>

namespace Cuboid
{

    void D3DVertexArray::Bind() const
    {

        m_vtxBuffer->Bind();
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
        vtxBuffer->Bind();
    }

    void D3DVertexArray::AddVertexBuffer(const Cuboid::Ref<Cuboid::VertexBuffer> &vtxBuffer)
    {
        m_vtxBuffer =  vtxBuffer;
        m_vtxBuffer->Bind();
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