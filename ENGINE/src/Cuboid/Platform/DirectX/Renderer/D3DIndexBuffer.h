//
// Created by Jerry on 19/6/2020.
//


#ifndef CUBOID_D3DINDEXBUFFER_H
#define CUBOID_D3DINDEXBUFFER_H

#include <Cuboid/Renderer/Buffer.h>

typedef struct ID3D11Buffer ID3D11Buffer;

namespace Cuboid
{

    class D3DIndexBuffer : public IndexBuffer
    {
        public:

        D3DIndexBuffer(uint32_t* indices, uint32_t count);

        virtual ~D3DIndexBuffer();

        void Bind() const override;

        void UnBind() const override;

        uint32_t GetCount() const override;

        private:

        ID3D11Buffer* m_pIndexBuffer;

        uint32_t m_Count = 0;
    };

}

#endif //CUBOID_D3DINDEXBUFFER_H
