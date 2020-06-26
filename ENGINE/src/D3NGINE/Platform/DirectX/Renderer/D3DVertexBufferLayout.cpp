//
// Created by Jerry on 24/6/2020.
//

#include "d3gpch.h"
#include "D3DVertexBufferLayout.h"
#include "D3DGraphicsContext.h"
#include "d3d11.h"
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
        D3DGraphicsContext::GetContext()->IASetInputLayout(m_VertexLayout);
    }

    BufferLayout &D3DVertexBufferLayout::GetBufferLayout() const
    {
        return const_cast<BufferLayout&>(m_Layout);
    }

    D3DVertexBufferLayout::D3DVertexBufferLayout(const BufferLayout &layout, const Ref<Shader>& shader):
    m_Layout(layout), m_Shader(shader)
    {

        const auto& elements = m_Layout.GetElements();
        D3D11_INPUT_ELEMENT_DESC* layoutBinding = new D3D11_INPUT_ELEMENT_DESC[elements.size()];
        UINT layoutsize = 0;
        for(int i = 0; i < elements.size(); i++){

            auto& element = elements[i];

            layoutBinding[i]  = { element.Name.c_str(), 0, ShaderDataTypeToD3D(element.Type), 0, (UINT)element.Offset,
                                  D3D11_INPUT_PER_VERTEX_DATA, 0};

            D3G_CORE_INFO("VERTEX ATRRIBS NAME {0}", element.Name);
            layoutsize++;
        }


        D3DGraphicsContext::GetDevice()->CreateInputLayout(layoutBinding,
                                                           layoutsize,
                                                           std::dynamic_pointer_cast<D3DShader>(m_Shader)->Get_VertexShaderSrcBlob()->GetBufferPointer(),
                                                           std::dynamic_pointer_cast<D3DShader>(m_Shader)->Get_VertexShaderSrcBlob()->GetBufferSize(),
                                                           &m_VertexLayout);


        delete[] layoutBinding;

    }

}