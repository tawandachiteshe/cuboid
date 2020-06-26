//
// Created by Jerry on 19/6/2020.
//

#ifndef D3NGINE_D3DSHADER_H
#define D3NGINE_D3DSHADER_H

#include <D3NGINE/Renderer/Shader.h>
#include <d3d11.h>

namespace D3G
{

    class D3DShader : public Shader
    {
        public:

        D3DShader(const std::string& pixelShaderSrc, const std::string& vertexShaderSrc);

        void Bind() override;

        void UnBind() override;

        void SetInt(const std::string &name, int value) override;

        void SetIntArray(const std::string &name, int *values, uint32_t count) override;

        void SetFloat(const std::string &name, float value) override;

        void SetFloat2(const std::string &name, const glm::vec2 &value) override;

        void SetFloat3(const std::string &name, const glm::vec3 &value) override;

        void SetFloat4(const std::string &name, const glm::vec4 &value) override;

        void SetMat4(const std::string &name, const glm::mat4 &value) override;

        ID3DBlob *Get_VertexShaderSrcBlob() const;

        ID3DBlob *Get_PixelShaderSrcBlob() const;

        private:

        ID3DBlob* m_VertexShaderSrcBlob;

        ID3DBlob* m_PixelShaderSrcBlob;

        void BindDefaultCB();

        D3D11_MAPPED_SUBRESOURCE m_ShaderRes;


        private:

        bool CompileShader(const char* src, const char* shaderType,ID3DBlob** blob);

        void CreateVertexShader();
        void CreatePixelShader();

        ID3D11VertexShader* m_VertexShader;

        ID3D11PixelShader* m_PixelShader;

        ID3DBlob* m_VertexShaderErrorBlob;

        ID3DBlob* m_PixelShaderErrorBlob;

        ID3D11Buffer* m_ShaderConstantBuffer;
    };



}
#endif //D3NGINE_D3DSHADER_H
