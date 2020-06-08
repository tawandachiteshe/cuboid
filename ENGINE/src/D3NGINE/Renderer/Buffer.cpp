#include <D3NGINE/Renderer/RendererAPI.h>
#include <D3NGINE/Renderer/Buffer.h>
#include <D3NGINE/Platform/OpenGL/OpenGLIndexBuffer.h>
#include <D3NGINE/Platform/OpenGL/OpenGLVertexBuffer.h>

namespace D3G
{
	Ref<IndexBuffer> IndexBuffer::Create(uint32_t* indices, uint32_t size)
	{
		switch(RendererAPI::GetAPI())
		{
		case RendererAPI::API::None: D3G_CORE_ERROR("None Currently not suppported! "); break;
		case RendererAPI::API::Opengl: return CreateRef<OpenGLIndexBuffer>(indices, size);
		}
		return nullptr;
	}

	Ref<VertexBuffer> VertexBuffer::Create(float* vertices, uint32_t size)
	{
		switch(RendererAPI::GetAPI())
		{
		case RendererAPI::API::None: D3G_CORE_ERROR("None Currently not supported! "); break;
		case RendererAPI::API::Opengl: return  CreateRef<OpenGLVertexBuffer>(vertices, size);
		}
		return nullptr;
	}

	Ref<VertexBuffer> VertexBuffer::Create(uint32_t size)
	{
		switch(RendererAPI::GetAPI())
		{
		case RendererAPI::API::None: D3G_CORE_ERROR("None Currently not supported! "); break;
		case RendererAPI::API::Opengl: return  CreateRef<OpenGLVertexBuffer>(size);
		}
		return nullptr;
	}

}
