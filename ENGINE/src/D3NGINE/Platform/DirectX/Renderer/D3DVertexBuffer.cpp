//
// Created by Jerry on 19/6/2020.
//
#include <d3gpch.h>
#include <cstdint>
#include "D3DVertexBuffer.h"
#include "D3DGraphicsContext.h"
#include "D3DShader.h"
#include "InitializeD3Devices.h"


namespace D3G
{

    static DXGI_FORMAT ShaderDataTypeToD3D(ShaderDataType dataType)
    {
        switch (dataType) {

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


    D3DVertexBuffer::D3DVertexBuffer(void* vertices, uint32_t size) :
        m_Layout({}), m_pInputLayout(0), m_pVertexBuffer(0), m_Shader(0)
    {
        HRESULT r = S_OK;

        D3D11_BUFFER_DESC buff_desc = {};
        buff_desc.Usage = D3D11_USAGE_DEFAULT;
        buff_desc.ByteWidth = size;
        buff_desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
        buff_desc.CPUAccessFlags = 0;
        buff_desc.MiscFlags = 0;

        D3D11_SUBRESOURCE_DATA init_data = {};
        init_data.pSysMem = vertices;


       r = GraphicsEngine()->GetDevice()->CreateBuffer(&buff_desc, &init_data, &m_pVertexBuffer);

       if(FAILED(r))
       {
           D3G_CORE_ERROR("D3D vertebuffer failed to create!!!!");
       }

       

    }

    D3DVertexBuffer::D3DVertexBuffer(uint32_t size)
    {

    }

    D3DVertexBuffer::~D3DVertexBuffer()
    {
        m_pInputLayout->Release();
        if(m_pInputLayout)
        {
            m_pInputLayout = nullptr;
        }

        m_pVertexBuffer->Release();
        if (m_pVertexBuffer)
        {
            m_pVertexBuffer = nullptr;
        }
    }

    void D3G::D3DVertexBuffer::Bind() const
    {
        UINT strides = m_Layout.GetStride();
        UINT offset = 0;

        GraphicsEngine()->GetContext()->IASetInputLayout(m_pInputLayout);

        GraphicsEngine()->GetContext()->IASetVertexBuffers(0, 1, &m_pVertexBuffer, &strides, &offset);

        

    }

    void D3G::D3DVertexBuffer::UnBind() const
    {

    }

    void D3G::D3DVertexBuffer::SetLayout(const BufferLayout &layout)
    {
        m_Layout = layout;

        HRESULT r = S_OK;
        D3D11_INPUT_ELEMENT_DESC *desc_layout = new D3D11_INPUT_ELEMENT_DESC[layout.GetElements().size()];

        auto& elements = layout.GetElements();

        for (UINT i = 0; i < layout.GetElements().size(); i++)
        {
            desc_layout[i] = { elements[i].Name.c_str(), 0, ShaderDataTypeToD3D(elements[i].Type), 0, elements[i].Offset, D3D11_INPUT_PER_VERTEX_DATA, 0 };
        }

        const auto& shader_byte_code = std::dynamic_pointer_cast<D3DShader>(m_Shader)->GetVertexShaderBuffer();

        r = GraphicsEngine()->GetDevice()->CreateInputLayout(desc_layout, layout.GetElements().size(), shader_byte_code->GetBufferPointer(), shader_byte_code->GetBufferSize(), &m_pInputLayout);

        if (FAILED(r))
        {
            D3G_CORE_ERROR("D3d devices Failed to Create Input layout");
        }

        delete[] desc_layout;
    }

    void D3G::D3DVertexBuffer::SetData(const void *data, uint32_t size)
    {
         
    }

    const BufferLayout& D3G::D3DVertexBuffer::GetBufferLayout() const
    {
        return m_Layout;
    }

    void D3DVertexBuffer::SetShader(const Ref<Shader>& shader)
    {
        m_Shader = shader;
    }

}