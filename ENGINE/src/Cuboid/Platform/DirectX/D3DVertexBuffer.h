//
// Created by Jerry on 19/6/2020.
//

#ifndef CUBOID_D3DVERTEXBUFFER_H
#define CUBOID_D3DVERTEXBUFFER_H

#include <Cuboid/Renderer/Buffer.h>
#include <cstdint>


namespace Cuboid
{
    class Shader;

    class ID3D11InputLayout;

    class D3DVertexBuffer : public VertexBuffer
    {
        public:

        D3DVertexBuffer(void* vertices, uint32_t size);

        D3DVertexBuffer(uint32_t size);

        virtual ~D3DVertexBuffer();

        void Bind() const override;

        void UnBind() const override;

        void SetLayout(const BufferLayout& layout) override;

        void SetData(const void *data, uint32_t size) override;

        const BufferLayout& GetBufferLayout() const override;

        void SetShader(const Ref<Shader>& shader);

        private:

        ID3D11Buffer* m_pVertexBuffer;

        BufferLayout m_Layout;

        ID3D11InputLayout* m_pInputLayout;

        Ref<Shader> m_Shader;

    };

}

#endif //CUBOID_D3DVERTEXBUFFER_H
