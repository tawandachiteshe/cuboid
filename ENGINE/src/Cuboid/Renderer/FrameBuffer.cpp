#include "Cuboidpch.h"
#include "FrameBuffer.h"
#include "Cuboid\Platform\DirectX\Renderer\D3DFramebuffers.h"
#include <Cuboid/Renderer/RendererAPI.h>

namespace Cuboid
{
	Ref<FrameBuffer> FrameBuffer::Create(const FrameBufferSpecification& spec)
	{
		switch (RendererAPI::GetAPI())
		{
		case RendererAPI::API::DirectX:
			return CreateRef<D3DFramebuffers>(spec);
		}
		
	}
}