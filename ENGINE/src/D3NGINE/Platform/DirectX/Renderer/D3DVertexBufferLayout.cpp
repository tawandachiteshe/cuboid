//
// Created by Jerry on 24/6/2020.
//

#include "d3gpch.h"
#include "D3DVertexBufferLayout.h"
#include "D3DGraphicsContext.h"

#include "D3DShader.h"
#include <D3NGINE/Renderer/Buffer.h>
#include <D3NGINE/Renderer/Shader.h>

namespace D3G
{

    static DXGI_FORMAT ShaderDataTypeToD3D(ShaderDataType dataType)
    {
        switch(dataType){

            case ShaderDataType::Float1:    return DXGI_FORMAT_R32_FLOAT;
            case ShaderDataType::Float2:    return DXGI_FORMAT_R32G32_FLOAT;
            case ShaderDataType::Float3:    return DXGI_FORMAT_R32G32B32_FLOAT;
            case ShaderDataType::Float4:    return DXGI_FORMAT_R32G32B32A32_FLOAT;

            case ShaderDataType::Int:       return DXGI_FORMAT_R32_SINT;
            case ShaderDataType::Int2:      return DXGI_FORMAT_R32G32_SINT;
            case ShaderDataType::Int3:      return DXGI_FORMAT_R32G32B32_SINT;
            case ShaderDataType::Int4:      return DXGI_FORMAT_R32G32B32A32_SINT;

        }
        return DXGI_FORMAT_UNKNOWN;
    }

    void D3DVertexBufferLayout::Bind()
    {
        
    }

    BufferLayout &D3DVertexBufferLayout::GetBufferLayout() const
    {
        return const_cast<BufferLayout&>(m_Layout);
    }

    D3DVertexBufferLayout::D3DVertexBufferLayout(const BufferLayout &layout, const Ref<Shader>& shader):
    m_Layout(layout), m_Shader(shader)
    {

    }

}