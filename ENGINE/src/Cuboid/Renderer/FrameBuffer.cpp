#include "Cuboidpch.h"
#include "FrameBuffer.h"
#include "Cuboid\Platform\DirectX\D3DFramebuffers.h"
#include <Cuboid\Renderer\RendererAPI.h>

namespace Cuboid
{
	Ref<FrameBuffer> FrameBuffer::Create(const FrameBufferSpecification& spec)
	{
		switch (RendererAPI::GetAPI())
		{
		case RendererAPI::API::DirectX:
			return CreateRef<D3DFramebuffers>(spec);
		case RendererAPI::API::Opengl:

			CUBOID_CORE_ASSERT(1, "The current supported opengl does'nt support framebuffer");
			return nullptr;
		}

		return nullptr;
		
	}
}