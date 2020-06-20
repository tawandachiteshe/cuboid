//
// Created by Jerry on 19/6/2020.
//

#include <d3gpch.h>
#include "D3DShader.h"
#include <d3dcompiler.h>

#include "D3DGraphicsContext.h"


namespace D3G
{
    struct DefaultShaderContantBuffer
    {
        INT defaultInt = 0;
        INT defaultIntArrayMax[32] = {0};

        FLOAT defaultFloat = 0.0f;
        FLOAT defaultFloat2[2] = {0};
        FLOAT defaultFloat3[3] = {0};
        FLOAT defaultFloat4[4] = {0};

        FLOAT defaultFloat4x4[4][4] = { { 0 } };

    };


    void D3DShader::Bind()
    {

        D3DGraphicsContext::GetContext()->VSSetShader(m_VertexShader, NULL, 0);
        D3DGraphicsContext::GetContext()->PSSetShader(m_PixelShader, NULL, 0);

        BindDefaultCB();

    }

    void D3DShader::BindDefaultCB()
    {

        D3DGraphicsContext::GetContext()->VSSetConstantBuffers(0, 1, &m_ShaderConstantBuffer);
        D3DGraphicsContext::GetContext()->PSSetConstantBuffers(0, 1, &m_ShaderConstantBuffer);

    }

    void D3DShader::UnBind()
    {

    }

    void D3DShader::SetInt(const std::string &name, int value)
    {
        D3DGraphicsContext::GetContext()->Map(m_ShaderConstantBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &m_ShaderRes);
        DefaultShaderContantBuffer* localConstBuffer =  (DefaultShaderContantBuffer*)m_ShaderRes.pData;

        memcpy(&localConstBuffer->defaultInt, &value, sizeof(int));
        D3DGraphicsContext::GetContext()->Unmap(m_ShaderConstantBuffer, 0);
    }

    void D3DShader::SetIntArray(const std::string &name, int *values, uint32_t count)
    {

        D3DGraphicsContext::GetContext()->Map(m_ShaderConstantBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &m_ShaderRes);
        DefaultShaderContantBuffer* localConstBuffer =  (DefaultShaderContantBuffer*)m_ShaderRes.pData;

        memcpy(&localConstBuffer->defaultIntArrayMax, values, sizeof(INT) * count);
        D3DGraphicsContext::GetContext()->Unmap(m_ShaderConstantBuffer, 0);

    }

    void D3DShader::SetFloat(const std::string &name, float value)
    {
        D3DGraphicsContext::GetContext()->Map(m_ShaderConstantBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &m_ShaderRes);
        DefaultShaderContantBuffer* localConstBuffer =  (DefaultShaderContantBuffer*)m_ShaderRes.pData;

        memcpy(&localConstBuffer->defaultFloat, &value, sizeof(FLOAT));
        D3DGraphicsContext::GetContext()->Unmap(m_ShaderConstantBuffer, 0);
    }

    void D3DShader::SetFloat2(const std::string &name, const glm::vec2 &value)
    {
        D3DGraphicsContext::GetContext()->Map(m_ShaderConstantBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &m_ShaderRes);
        DefaultShaderContantBuffer* localConstBuffer =  (DefaultShaderContantBuffer*)m_ShaderRes.pData;

        memcpy(&localConstBuffer->defaultFloat2, &value, sizeof(FLOAT));
        D3DGraphicsContext::GetContext()->Unmap(m_ShaderConstantBuffer, 0);

    }

    void D3DShader::SetFloat3(const std::string &name, const glm::vec3 &value)
    {
        D3DGraphicsContext::GetContext()->Map(m_ShaderConstantBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &m_ShaderRes);
        DefaultShaderContantBuffer* localConstBuffer =  (DefaultShaderContantBuffer*)m_ShaderRes.pData;

        memcpy(&localConstBuffer->defaultFloat3, &value, sizeof(FLOAT));
        D3DGraphicsContext::GetContext()->Unmap(m_ShaderConstantBuffer, 0);

    }

    void D3DShader::SetFloat4(const std::string &name, const glm::vec4 &value)
    {
        D3DGraphicsContext::GetContext()->Map(m_ShaderConstantBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &m_ShaderRes);
        DefaultShaderContantBuffer* localConstBuffer =  (DefaultShaderContantBuffer*)m_ShaderRes.pData;

        memcpy(&localConstBuffer->defaultFloat4, &value, sizeof(FLOAT));
        D3DGraphicsContext::GetContext()->Unmap(m_ShaderConstantBuffer, 0);

    }

    void D3DShader::SetMat4(const std::string &name, const glm::mat4 &value)
    {
        D3DGraphicsContext::GetContext()->Map(m_ShaderConstantBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &m_ShaderRes);
        DefaultShaderContantBuffer* localConstBuffer =  (DefaultShaderContantBuffer*)m_ShaderRes.pData;

        memcpy(&localConstBuffer->defaultFloat4x4, &value, sizeof(FLOAT));
        D3DGraphicsContext::GetContext()->Unmap(m_ShaderConstantBuffer, 0);
    }

    D3DShader::D3DShader(const std::string &pixelShaderSrc, const std::string &vertexShaderSrc)
    {

        {

        bool VertexShaderCompileStatus =
                D3DCompile(vertexShaderSrc.c_str(), vertexShaderSrc.size(), NULL, NULL, NULL, "main", "vs_4_0",
                           0, 0, &m_VertexShaderSrcBlob, &m_VertexShaderErrorBlob) != S_OK;

        if (!VertexShaderCompileStatus) {
            D3G_CORE_INFO("D3D Vertex Shader compiled successfully!!!");

            bool PixelShaderCreationStatus = D3DGraphicsContext::GetDevice()->CreateVertexShader(
                    m_VertexShaderSrcBlob->GetBufferPointer(), m_VertexShaderSrcBlob->GetBufferSize(),
                    NULL, &m_VertexShader) != S_OK;

            if (!PixelShaderCreationStatus)
                D3G_CORE_INFO("D3D Vertex Shader created successfully!!!");
            else
                D3G_CORE_ERROR("D3D Vertex Shader creation failed ;(");

            //m_VertexShaderSrcBlob->Release();

        } else {

            D3G_CORE_ERROR("D3D Vertex Shader FAILED to COMPILEY ;(");
        }

        D3G_CORE_CRITICAL("Error compiling d3d vertex shader {0}: ",
                          (const char *) m_VertexShaderErrorBlob->GetBufferPointer());
    }

        {
            //TODO: CHECK SOME CLEAN UP HERE
            D3D11_BUFFER_DESC desc;
            ZeroMemory(&desc, sizeof(desc));
            desc.ByteWidth = sizeof(DefaultShaderContantBuffer);
            desc.Usage = D3D11_USAGE_DYNAMIC;
            desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
            desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
            desc.MiscFlags = 0;

            D3DGraphicsContext::GetDevice()->CreateBuffer(&desc, NULL, &m_ShaderConstantBuffer);

        }

        {
            bool PixelShaderCompileStatus =
                    D3DCompile(pixelShaderSrc.c_str(), vertexShaderSrc.size(), NULL, NULL, NULL, "main", "ps_4_0",
                               0, 0, &m_PixelShaderSrcBlob, &m_PixelShaderErrorBlob) != S_OK;

            if (!PixelShaderCompileStatus) {
                D3G_CORE_INFO("D3D Pixel Shader compiled successfully!!!");

                bool PixelShaderCreationStatus = D3DGraphicsContext::GetDevice()->CreatePixelShader(
                        m_PixelShaderSrcBlob->GetBufferPointer(), m_PixelShaderSrcBlob->GetBufferSize(),
                        NULL, &m_PixelShader) != S_OK;

                if (!PixelShaderCreationStatus)
                    D3G_CORE_INFO("D3D Pixel Shader created successfully!!!");
                else
                    D3G_CORE_ERROR("D3D Pixel Shader creation failed ;(");

                //m_PixelShaderSrcBlob->Release();

            } else {

                D3G_CORE_ERROR("D3D Pixel Shade ;(");

            }

            D3G_CORE_CRITICAL("Error compiling d3d pixel shader {0}: ",
                              (const char *) m_PixelShaderErrorBlob->GetBufferPointer());
        }

        if(m_PixelShaderErrorBlob != nullptr)
            m_PixelShaderErrorBlob->Release();

        if(m_VertexShaderErrorBlob != nullptr)
            m_VertexShaderErrorBlob->Release();

    }

    ID3DBlob *D3DShader::Get_VertexShaderSrcBlob() const
    {
        return m_VertexShaderSrcBlob;
    }

    ID3DBlob *D3DShader::Get_PixelShaderSrcBlob() const
    {
        return m_PixelShaderSrcBlob;
    }

    void D3DShader::CreateVertexShader()
    {

    }

    void D3DShader::CreatePixelShader()
    {

    }

}