//
// Created by Jerry on 24/6/2020.
//

#ifndef D3NGINE_D3DVERTEXBUFFERLAYOUT_H
#define D3NGINE_D3DVERTEXBUFFERLAYOUT_H

#include <D3NGINE/Renderer/VertexBufferLayout.h>

typedef struct ID3D11InputLayout ID3D11InputLayout;
namespace D3G
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

#endif //D3NGINE_D3DVERTEXBUFFERLAYOUT_H
