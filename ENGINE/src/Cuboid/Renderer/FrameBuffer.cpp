#include "Cuboidpch.h"
#include "FrameBuffer.h"
#ifdef WIN32
#include "Cuboid\Platform\DirectX\D3DFramebuffers.h"
#endif
#include <Cuboid/Renderer/RendererAPI.h>

namespace Cuboid
{
	Ref<FrameBuffer> FrameBuffer::Create(const FrameBufferSpecification& spec)
	{
		switch (RendererAPI::GetAPI())
		{
		case RendererAPI::API::DirectX:
#ifdef WIN32
			return CreateRef<D3DFramebuffers>(spec);
#endif
		case RendererAPI::API::Opengl:

			CUBOID_CORE_ASSERT(1, "The current supported opengl does'nt support framebuffer");
			return nullptr;
		}

		return nullptr;
		
	}
}