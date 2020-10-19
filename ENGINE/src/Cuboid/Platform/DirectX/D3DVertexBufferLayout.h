//
// Created by Jerry on 24/6/2020.
//

#ifndef CUBOID_D3DVERTEXBUFFERLAYOUT_H
#define CUBOID_D3DVERTEXBUFFERLAYOUT_H

#include <Cuboid/Renderer/VertexBufferLayout.h>

typedef struct ID3D11InputLayout ID3D11InputLayout;
namespace Cuboid
{
    class Shader;
    class D3DVertexBufferLayout : public VertexBufferLayout
    {
        public:
        D3DVertexBufferLayout(const BufferLayout& layout, const Ref<Shader>& shader);

        void Bind() override;

        BufferLayout &GetBufferLayout() const override;

        private:
        const BufferLayout& m_Layout;

        ID3D11InputLayout* m_VertexLayout;

        Ref<Shader> m_Shader;


    };

}

#endif //CUBOID_D3DVERTEXBUFFERLAYOUT_H
