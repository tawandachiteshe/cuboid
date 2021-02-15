//
// Created by Jerry on 10/6/2020.
//

#ifndef CUBOID_D3DRENDERERAPI_H
#define CUBOID_D3DRENDERERAPI_H
#include <Cuboid/Renderer/RendererAPI.h>
#include "Cuboid/Platform/DirectX/InitializeD3Devices.h"

typedef class ID3D11RenderTargetView ID3D11RenderTargetView;
class ID3D11BlendState;
class ID3D11RasterizerState;
namespace Cuboid
{

    class D3DRendererAPI : public RendererAPI
    {
        public:
        void Init() override;

        void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) override;

        void SetClearColor(const glm::vec4 &clearColor) override;

        void Clear() override;

        void DrawIndexed(const Ref <VertexArray> &vertexArray, uint32_t indexCount, uint32_t mode) override;

        private:

        static ID3D11RenderTargetView*  m_mainRenderTargetView;
        static ID3D11BlendState* m_pBlendState;
        static ID3D11RasterizerState* m_pRasterizerState;


        // Inherited via RendererAPI
        virtual void Draw(const Ref<VertexArray>& vertexArray, uint32_t vertexCount, uint32_t startVertex) override;

    };

}
#endif //CUBOID_D3DRENDERERAPI_H
