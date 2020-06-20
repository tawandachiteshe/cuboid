#include <d3gpch.h>

#include <D3NGINE/Renderer/RendererAPI.h>
#include <D3NGINE/Renderer/Buffer.h>
#include <D3NGINE/Platform/OpenGL/OpenGLIndexBuffer.h>
#include <D3NGINE/Platform/OpenGL/OpenGLVertexBuffer.h>

#include <D3NGINE/Platform/DirectX/Renderer/D3DIndexBuffer.h>
#include <D3NGINE/Platform/DirectX/Renderer/D3DVertexBuffer.h>

namespace D3G
{
	Ref<IndexBuffer> IndexBuffer::Create(uint32_t* indices, uint32_t count)
	{
		switch(RendererAPI::GetAPI())
		{
		case RendererAPI::API::None: D3G_CORE_ERROR("None Currently not suppported! "); break;
		case RendererAPI::API::Opengl: return CreateRef<OpenGLIndexBuffer>(indices, count);
		case RendererAPI::API::DirectX: return CreateRef<D3DIndexBuffer>(indices, count);
		}
		return nullptr;
	}

	///////////////////Vertex Buffer here!!!!!/////////////////////
	Ref<VertexBuffer> VertexBuffer::Create(float* vertices, uint32_t size)
	{
		switch(RendererAPI::GetAPI())
		{
		case RendererAPI::API::None: D3G_CORE_ERROR("None Currently not supported! "); break;
		case RendererAPI::API::Opengl: return  CreateRef<OpenGLVertexBuffer>(vertices, size);
		case RendererAPI::API::DirectX: return  CreateRef<D3DVertexBuffer>(vertices, size);
		}
		return nullptr;
	}

	Ref<VertexBuffer> VertexBuffer::Create(uint32_t size)
	{
		switch(RendererAPI::GetAPI())
		{
		case RendererAPI::API::None: D3G_CORE_ERROR("None Currently not supported! "); break;
		case RendererAPI::API::Opengl: return  CreateRef<OpenGLVertexBuffer>(size);
		case RendererAPI::API::DirectX: return  CreateRef<D3DVertexBuffer>(size);

		}
		return nullptr;
	}

}
