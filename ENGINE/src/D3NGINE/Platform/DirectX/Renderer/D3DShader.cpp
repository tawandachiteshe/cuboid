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

    };


    void D3DShader::Bind()
    {

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


    }

    ID3DBlob *D3DShader::Get_VertexShaderSrcBlob() const
    {
        return nullptr;
    }

    ID3DBlob *D3DShader::Get_PixelShaderSrcBlob() const
    {
        return nullptr;
    }

    void D3DShader::CreateVertexShader()
    {

    }

    void D3DShader::CreatePixelShader()
    {

    }


    bool D3DShader::CompileShader(const char *src, const char* shaderType, ID3DBlob **blob)
    {

        return false;
    }

}