//
// Created by Jerry on 19/6/2020.
//

#ifndef CUBOID_D3DSHADER_H
#define CUBOID_D3DSHADER_H

#include <Cuboid/Renderer/Shader.h>
#include <unordered_map>

#ifdef WIN32
#include <DirectXMath.h>
#endif

namespace Cuboid
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

        void SetPointerArray(const std::string& name, void* values, uint32_t count) override;


        void SetConstantBuffer(const Ref<ConstantBuffer>& buffer) override 
        {
            m_Buffer = buffer;
            m_PixelConstantBuffers = buffer->GetPixelConstantBuffers();
            m_VertexConstantBuffers = buffer->GetVertexConstantBuffers();

            m_VertexConstantBuffers.insert(m_VertexConstantBuffers.begin(), m_pVertexShaderConstantBuffer);
        
        }

        Ref<ConstantBuffer>& GetConstantBuffer() override { return m_Buffer; }

        ID3DBlob * GetVertexShaderBuffer() const;

        ID3DBlob * GetPixelShaderBuffer() const;

        ID3DBlob* m_pVertexShaderBuffer;

        ID3DBlob* m_pPixelShaderBuffer;

        void BindDefaultCB();

        D3D11_MAPPED_SUBRESOURCE m_ShaderRes;


        private:

        bool CompileShader(const std::string& src, const char* shaderType,ID3DBlob** blob);

        void CreateVertexShader();
        void CreatePixelShader();



        ID3D11VertexShader* m_VertexShader;

        ID3D11PixelShader* m_PixelShader;

        ID3D11Buffer* m_pVertexShaderConstantBuffer;

        ID3D11Buffer* m_pPixelShaderConstantBuffer;

        std::vector<ID3D11Buffer*> m_VertexConstantBuffers;

        std::vector<ID3D11Buffer*> m_PixelConstantBuffers;

        Ref<ConstantBuffer> m_Buffer;

    };

}
#endif //CUBOID_D3DSHADER_H
