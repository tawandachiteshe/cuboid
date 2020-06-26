//
// Created by Jerry on 19/6/2020.
//

#include <d3gpch.h>
#include "D3DShader.h"
#include <d3dcompiler.h>
#include <glm/gtc/type_ptr.hpp>
#include <DirectXMath.h>
#include "D3DGraphicsContext.h"


namespace D3G
{
    struct DefaultShaderContantBuffer
    {
        DirectX::XMFLOAT4X4 ProjectionMatrix;
    };


    void D3DShader::Bind()
    {

        D3DGraphicsContext::GetContext()->VSSetShader(m_VertexShader, NULL, 0);
        BindDefaultCB();
        D3DGraphicsContext::GetContext()->PSSetShader(m_PixelShader, NULL, 0);


    }

    void D3DShader::BindDefaultCB()
    {

        D3DGraphicsContext::GetContext()->VSSetConstantBuffers(0, 1, &m_ShaderConstantBuffer);

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

        D3DGraphicsContext::GetContext()->Map(m_ShaderConstantBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &m_ShaderRes);
        auto* localConstBuffer =  (DefaultShaderContantBuffer*)m_ShaderRes.pData;

        auto xmmatrix = DirectX::XMMatrixOrthographicLH(1278.0f, 600.0f, 0.1f, 1.0f);

        DirectX::XMStoreFloat4x4(&localConstBuffer->ProjectionMatrix, xmmatrix);
        //memcpy(&localConstBuffer->ProjectionMatrix, &value, sizeof(value));

        D3DGraphicsContext::GetContext()->Unmap(m_ShaderConstantBuffer, 0);
    }

    D3DShader::D3DShader(const std::string &pixelShaderSrc, const std::string &vertexShaderSrc)
    {

            //TODO: CHECK SOME CLEAN UP HERE
            D3D11_BUFFER_DESC desc;
            ZeroMemory(&desc, sizeof(desc));
            desc.ByteWidth = sizeof(DefaultShaderContantBuffer);
            desc.Usage = D3D11_USAGE_DYNAMIC;
            desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
            desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
            desc.MiscFlags = 0;
            desc.StructureByteStride = 0;


            D3G_CORE_INFO("constant buffers {0}",
                          D3DGraphicsContext::GetDevice()->CreateBuffer(&desc, NULL, &m_ShaderConstantBuffer) != S_OK);



        //compile pixel shader
        if(CompileShader(pixelShaderSrc.c_str(), "ps_4_0", &m_PixelShaderSrcBlob)) {


            bool creationStatus = D3DGraphicsContext::GetDevice()->CreatePixelShader(m_PixelShaderSrcBlob->GetBufferPointer(),
                                                               m_PixelShaderSrcBlob->GetBufferSize(), NULL, &m_PixelShader) != S_OK;

            const char* wordStatus = creationStatus ? "Failed" : "Success";

            D3G_CORE_INFO("Creation of Pixel shader was {0}", wordStatus);
        }

        //compile pixel shader
        if(CompileShader(vertexShaderSrc.c_str(), "vs_4_0", &m_VertexShaderSrcBlob)) {


            bool creationStatus = D3DGraphicsContext::GetDevice()->CreateVertexShader(m_VertexShaderSrcBlob->GetBufferPointer(),
                                                                                     m_VertexShaderSrcBlob->GetBufferSize(), NULL, &m_VertexShader) != S_OK;

            const char* wordStatus = creationStatus ? "Failed" : "Success";

            D3G_CORE_INFO("Creation of Vertex shader was {0}", wordStatus);
        }




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


    bool D3DShader::CompileShader(const char *src, const char* shaderType, ID3DBlob **blob)
    {
        ID3DBlob *errorBlob;
        ID3DBlob *srcBlob;

        bool compilationStatus = false;

        compilationStatus = D3DCompile(src, strlen(src), NULL, NULL, NULL, "main", shaderType,
                                       0, 0, &srcBlob, &errorBlob) != S_OK;

        if (compilationStatus) {
            D3G_CORE_ERROR("Failed to compile {0} \n\n {1}", (const char *) errorBlob->GetBufferPointer());
            errorBlob->Release();
            return false;
        } else {

            *blob = srcBlob;
            return true;
        }



    }

}