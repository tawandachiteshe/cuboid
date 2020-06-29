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

    }

    D3DVertexBuffer::D3DVertexBuffer(uint32_t size)
    {

    }

    D3DVertexBuffer::~D3DVertexBuffer()
    {

    }

    void D3G::D3DVertexBuffer::Bind() const
    {

    }

    void D3G::D3DVertexBuffer::UnBind() const
    {

    }

    void D3G::D3DVertexBuffer::SetLayout(const BufferLayout &layout)
    {

    }

    void D3G::D3DVertexBuffer::SetData(const void *data, uint32_t size)
    {

    }

    const BufferLayout& D3G::D3DVertexBuffer::GetBufferLayout() const
    {
        return m_Layout;
    }

    void D3DVertexBuffer::CreateVertexBufferNow()
    {

    }

}