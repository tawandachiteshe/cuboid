#pragma once

#include "Cuboid\Core\Core.h"

namespace Cuboid
{
	struct FrameBufferSpecification
	{
		uint32_t Width, Height;
		uint32_t Samples = 1;

		bool SwapChainTarget = false;

		float BufferClearColor[4] = { 0.23f, 0.23f, 0.23f, 1.0f };
	};


	class FrameBuffer
	{
	public:
		
		//virtual FrameBufferSpecification& GetSpecification() = 0;
		virtual const FrameBufferSpecification& GetSpecification() const = 0;

		virtual void Bind() const = 0;

		virtual void UnBind() const = 0;

		static Ref<FrameBuffer> Create(const FrameBufferSpecification& spec);

		virtual void* GetColorAttachmentRenderID() const = 0;

		virtual void Resize(uint32_t width, uint32_t height) = 0;

	};
}