//
// Created by Jerry on 24/6/2020.
//

#include <d3gpch.h>
#include <D3NGINE/Platform/DirectX/Renderer/D3DVertexBufferLayout.h>
#include "VertexBufferLayout.h"
#include "RendererAPI.h"

namespace D3G
{

    Ref<VertexBufferLayout> VertexBufferLayout::Create(const BufferLayout &layout, const Ref<Shader>& shader)
    {
        switch (RendererAPI::GetAPI())
        {

            case RendererAPI::API::DirectX:
                return CreateRef<D3DVertexBufferLayout>(layout, shader);
            case RendererAPI::API::Opengl:
                D3G_CORE_ASSERT(false, "Please for opengl kindly define the layout using VertexArray");
                return nullptr;

        }
        return nullptr;
    }

}