//
// Created by Jerry on 19/6/2020.
//

#ifndef D3NGINE_D3DVERTEXARRAY_H
#define D3NGINE_D3DVERTEXARRAY_H


#include <D3NGINE/Renderer/VertexArray.h>



namespace D3G
{

    class D3DVertexArray : public VertexArray
    {

        public:

        D3DVertexArray();

        void Bind() const override;

        void UnBind() const override;

        const Ref <IndexBuffer> &GetIndexBuffer() const override;

        void AddVertexBuffer(const Ref <VertexBuffer> &vtxBuffer) const override;

        void SetIndexBuffer(const Ref <IndexBuffer> &idxBuffer) override;

        void SetShader(const Ref<Shader> &mShader) override;

        virtual ~D3DVertexArray();

        void AddVertexBuffer(const Ref<VertexBuffer> &vtxBuffer) override;

        private:

        Ref<IndexBuffer> m_IdxBuffer;

        Ref<Shader> m_Shader;

    };

}


#endif //D3NGINE_D3DVERTEXARRAY_H
