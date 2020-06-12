//
// Created by Jerry on 10/6/2020.
//

#ifndef D3NGINE_D3DRENDERERAPI_H
#define D3NGINE_D3DRENDERERAPI_H
#include <D3NGINE/Renderer/RendererAPI.h>
#include <d3gpch.h>

namespace D3G
{

    class D3DRendererAPI : public RendererAPI
    {
        public:
        void Init() override;

        void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) override;

        void SetClearColor(const glm::vec4 &clearColor) override;

        void Clear() override;

        void DrawIndexed(const Ref <VertexArray> &vertexArray, uint32_t indexCount, uint32_t mode) override;
    };

}
#endif //D3NGINE_D3DRENDERERAPI_H
