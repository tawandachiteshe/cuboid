//
// Created by Jerry on 19/6/2020.
//

#ifndef D3NGINE_D3DVERTEXBUFFER_H
#define D3NGINE_D3DVERTEXBUFFER_H

#include <D3NGINE/Renderer/Buffer.h>
#include <cstdint>


typedef struct ID3D11Buffer ID3D11Buffer;

namespace D3G
{

    class D3DVertexBuffer : public VertexBuffer
    {
        public:

        D3DVertexBuffer(float* vertices, uint32_t size);

        D3DVertexBuffer(uint32_t size);

        void Bind() const override;

        void UnBind() const override;

        void SetLayout(const BufferLayout& layout) override;

        void SetData(const void *data, uint32_t size) override;

        const BufferLayout& GetBufferLayout() const override;


        virtual ~D3DVertexBuffer();

        private:

        ID3D11Buffer* m_VertexBuffer;

        BufferLayout m_Layout;

    };

}

#endif //D3NGINE_D3DVERTEXBUFFER_H
