//
// Created by Jerry on 19/6/2020.
//

#include <d3gpch.h>
#include "D3DShader.h"
#include <d3dcompiler.h>
#include <glm/gtc/type_ptr.hpp>
#include <DirectXMath.h>
#include "D3DGraphicsContext.h"
#include "InitializeD3Devices.h"


namespace D3G
{
    struct DefaultShaderContantBuffer
    {

    };


    void D3DShader::Bind()
    {
        GraphicsEngine()->GetContext()->VSSetShader(m_VertexShader, nullptr, 0);
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


    }

    D3DShader::D3DShader(const std::string &pixelShaderSrc, const std::string &vertexShaderSrc)
    {
        bool is_shader_cool = false;
        HRESULT hr = S_OK;

        CompileShader(pixelShaderSrc, "ps_4_0", &m_pPixelShaderBuffer);
   
            

       CompileShader(vertexShaderSrc, "vs_4_0", &m_pVertexShaderBuffer);

        hr = GraphicsEngine()->GetDevice()->CreatePixelShader(m_pPixelShaderBuffer->GetBufferPointer(), m_pPixelShaderBuffer->GetBufferSize(), NULL, &m_PixelShader);


        if(FAILED(hr))
        {
            D3G_CORE_ERROR("Pixel shader failed to create!!!");
        }

        hr = GraphicsEngine()->GetDevice()->CreateVertexShader(m_pVertexShaderBuffer->GetBufferPointer(), m_pVertexShaderBuffer->GetBufferSize(), NULL, &m_VertexShader);

        if (FAILED(hr))
        {
            D3G_CORE_ERROR("Vertex shader failed to create!!!");
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

        D3DCompile(src.c_str(), strlen(src.c_str()), NULL, NULL, NULL, "main", shaderType, 0, 0, blob, &error_blob);

        if(FAILED(r))
        {
            D3G_CORE_ERROR("D3DSHADER failed to compile");
            if (error_blob)
                error_blob->Release();
            return false;
        }

        return true;

        
    }

}