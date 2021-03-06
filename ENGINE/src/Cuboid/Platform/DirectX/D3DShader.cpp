//
// Created by Jerry on 19/6/2020.
//

#include <Cuboidpch.h>
#include "D3DShader.h"
#include <d3dcompiler.h>
#include <glm/gtc/type_ptr.hpp>
#include "InitializeD3Devices.h"
#include "Cuboid\Renderer\Lights.h"


namespace Cuboid
{
    struct VERTEX_CONSTANT_BUFFER
    {
        glm::mat4 mvp;
    };

    void D3DShader::Bind()
    {
        GraphicsEngine()->GetContext()->VSSetShader(m_VertexShader, nullptr, 0);
        GraphicsEngine()->GetContext()->VSSetConstantBuffers(0, (UINT)m_VertexConstantBuffers.size(), &m_VertexConstantBuffers[0]);

        if (m_PixelConstantBuffers.size() != 0)
        {
            GraphicsEngine()->GetContext()->PSSetConstantBuffers(0, (UINT)m_PixelConstantBuffers.size(), &m_PixelConstantBuffers[0]);
        }

        GraphicsEngine()->GetContext()->PSSetShader(m_PixelShader, nullptr, 0);
    }

    void D3DShader::BindDefaultCB()
    {

    }

    void D3DShader::UnBind()
    {

    }

    void D3DShader::SetInt(const std::string &name, int value)
    {

    }

    void D3DShader::SetIntArray(const std::string &name, int *values, uint32_t count)
    {


    }

    void D3DShader::SetFloat(const std::string &name, float value)
    {

    }

    void D3DShader::SetFloat2(const std::string &name, const glm::vec2 &value)
    {


    }

    void D3DShader::SetFloat3(const std::string &name, const glm::vec3 &value)
    {
        
    }

    void D3DShader::SetFloat4(const std::string &name, const glm::vec4 &value)
    {


    }

    void D3DShader::SetMat4(const std::string &name, const glm::mat4 &value)
    {

        D3D11_MAPPED_SUBRESOURCE mapped_resource;

        if (GraphicsEngine()->GetContext()->Map(m_pVertexShaderConstantBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mapped_resource) != S_OK)
            CUBOID_CORE_ERROR("FAILED TO MAP VERTEX SHADER CONSTANT BUFFER");

        VERTEX_CONSTANT_BUFFER* constant_buffer = (VERTEX_CONSTANT_BUFFER*)mapped_resource.pData;

        memcpy(&constant_buffer->mvp, &value, sizeof(value));

        GraphicsEngine()->GetContext()->Unmap(m_pVertexShaderConstantBuffer, 0);

    }

    void D3DShader::SetPointerArray(const std::string& name, void* values, uint32_t count)
    {
      
    }

    D3DShader::D3DShader(const std::string &pixelShaderSrc, const std::string &vertexShaderSrc)
    {
        {
            HRESULT hr = S_OK;

            D3D11_BUFFER_DESC vertex_desc;
            vertex_desc.ByteWidth = sizeof(VERTEX_CONSTANT_BUFFER);
            vertex_desc.Usage = D3D11_USAGE_DYNAMIC;
            vertex_desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
            vertex_desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
            vertex_desc.MiscFlags = 0;
            vertex_desc.StructureByteStride = 0;
            hr = GraphicsEngine()->GetDevice()->CreateBuffer(&vertex_desc, NULL, &m_pVertexShaderConstantBuffer);

            m_VertexConstantBuffers.push_back(m_pVertexShaderConstantBuffer);
           

        }
        bool is_shader_cool = false;
        HRESULT hr = S_OK;

        CompileShader(pixelShaderSrc, "ps_4_0", &m_pPixelShaderBuffer);
   
            

       CompileShader(vertexShaderSrc, "vs_4_0", &m_pVertexShaderBuffer);

        hr = GraphicsEngine()->GetDevice()->CreatePixelShader(m_pPixelShaderBuffer->GetBufferPointer(), m_pPixelShaderBuffer->GetBufferSize(), NULL, &m_PixelShader);


        if(FAILED(hr))
        {
            CUBOID_CORE_ERROR("Pixel shader failed to create!!!");
        }

        hr = GraphicsEngine()->GetDevice()->CreateVertexShader(m_pVertexShaderBuffer->GetBufferPointer(), m_pVertexShaderBuffer->GetBufferSize(), NULL, &m_VertexShader);

        if (FAILED(hr))
        {
            CUBOID_CORE_ERROR("Vertex shader failed to create!!!");
        }

    }

    ID3DBlob *D3DShader::GetVertexShaderBuffer() const
    {
        return m_pVertexShaderBuffer;
    }

    ID3DBlob *D3DShader::GetPixelShaderBuffer() const
    {
        return m_pPixelShaderBuffer;
    }

    void D3DShader::CreateVertexShader()
    {

    }

    void D3DShader::CreatePixelShader()
    {

    }


    bool D3DShader::CompileShader(const std::string& src, const char* shaderType,  ID3DBlob **blob)
    {
        HRESULT r = S_OK;
        ID3DBlob* error_blob = nullptr;

        r = D3DCompile(src.c_str(), strlen(src.c_str()), NULL, NULL, NULL, "main", shaderType, 0, 0, blob, &error_blob);

        if(FAILED(r))
        {
            CUBOID_CORE_ERROR("D3DSHADER failed to compile: {0} ", (const char *)error_blob->GetBufferPointer());
            if (error_blob)
                error_blob->Release();
            return false;
        }

        return true;

        
    }

#if 0

    

#endif 
}