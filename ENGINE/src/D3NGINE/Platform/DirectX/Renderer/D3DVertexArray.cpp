//
// Created by Jerry on 19/6/2020.
//

#include <d3gpch.h>
#include "D3DVertexArray.h"
#include "D3DGraphicsContext.h"
#include "D3DShader.h"

#include <d3d11.h>

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
    }

    void D3DVertexArray::Bind() const
    {

        D3DGraphicsContext::GetContext()->IASetInputLayout(m_VertexLayout);

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
#if CONST_ADD_VERTEX_BUFFER

        Bind();
        vtxBuffer->Bind();
        std::vector<D3D11_INPUT_ELEMENT_DESC> layoutBinding;
        const auto& elements = vtxBuffer->GetBufferLayout().GetElements();

        for(int i = 0; i < elements.size(); i++){

            auto& element = elements[i];

            D3D11_INPUT_ELEMENT_DESC desc = { element.Name.c_str(), 0, ShaderDataTypeToD3D(element.Type), 0, (size_t)element.Offset,
                                              D3D11_INPUT_PER_VERTEX_DATA, 0};
            layoutBinding.push_back(desc);

            D3G_CORE_INFO("VERTEX ATRRIBS NAME {0}", element.Name);
        }



        void* pVoid = std::dynamic_pointer_cast<D3DShader>(m_Shader)->Get_PixelShaderSrcBlob()->GetBufferPointer();
        size_t BufferSize = std::dynamic_pointer_cast<D3DShader>(m_Shader)->Get_PixelShaderSrcBlob()->GetBufferSize();

        D3DGraphicsContext::GetDevice()->CreateInputLayout(layoutBinding.data(),
                                                           layoutBinding.size(),
                                                           pVoid,
                                                           (UINT)BufferSize,
                                                           &m_VertexLayout);

#endif
    }

    void D3DVertexArray::AddVertexBuffer(const D3G::Ref<D3G::VertexBuffer> &vtxBuffer)
    {

        Bind();
        vtxBuffer->Bind();
        std::vector<D3D11_INPUT_ELEMENT_DESC> layoutBinding;
        const auto& elements = vtxBuffer->GetBufferLayout().GetElements();

        for(int i = 0; i < elements.size(); i++){

            auto& element = elements[i];

            D3D11_INPUT_ELEMENT_DESC desc = { element.Name.c_str(), 0, ShaderDataTypeToD3D(element.Type), 0, (size_t)element.Offset,
                                              D3D11_INPUT_PER_VERTEX_DATA, 0};
            layoutBinding.push_back(desc);

            D3G_CORE_INFO("VERTEX ATRRIBS NAME {0}", element.Name);
        }



        void* pVoid = std::dynamic_pointer_cast<D3DShader>(m_Shader)->Get_PixelShaderSrcBlob()->GetBufferPointer();
        size_t BufferSize = std::dynamic_pointer_cast<D3DShader>(m_Shader)->Get_PixelShaderSrcBlob()->GetBufferSize();

        D3DGraphicsContext::GetDevice()->CreateInputLayout(layoutBinding.data(),
                                                           layoutBinding.size(),
                                                           pVoid,
                                                           (UINT)BufferSize,
                                                           &m_VertexLayout);

    }

    void D3DVertexArray::SetIndexBuffer(const Ref <IndexBuffer>& idxBuffer)
    {

        idxBuffer->Bind();
        m_IdxBuffer = idxBuffer;

    }

    D3DVertexArray::D3DVertexArray()
    {

    }

    D3DVertexArray::~D3DVertexArray()
    {
        m_VertexLayout = nullptr;
    }

    void D3DVertexArray::SetShader(const Ref<Shader>& mShader)
    {
        mShader->Bind();
        m_Shader = mShader;
    }
}