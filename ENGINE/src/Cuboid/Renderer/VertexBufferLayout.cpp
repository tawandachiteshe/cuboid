//
// Created by Jerry on 24/6/2020.
//

#include <Cuboidpch.h>
#include <Cuboid/Platform/DirectX/D3DVertexBufferLayout.h>
#include "VertexBufferLayout.h"
#include "RendererAPI.h"

namespace Cuboid
{

    Ref<VertexBufferLayout> VertexBufferLayout::Create(const BufferLayout &layout, const Ref<Shader>& shader)
    {
        switch (RendererAPI::GetAPI())
        {

            case RendererAPI::API::DirectX:
                return CreateRef<D3DVertexBufferLayout>(layout, shader);
            case RendererAPI::API::Opengl:
                CUBOID_CORE_ASSERT(false, "Please for opengl kindly define the layout using VertexArray");
                return nullptr;

        }
        return nullptr;
    }

}