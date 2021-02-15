#include <Cuboidpch.h>

#include <Cuboid/Renderer/RendererAPI.h>
#include <Cuboid/Renderer/Buffer.h>
#include <Cuboid/Platform/OpenGL/OpenGLIndexBuffer.h>
#include <Cuboid/Platform/OpenGL/OpenGLVertexBuffer.h>

#include <Cuboid/Platform/DirectX/D3DIndexBuffer.h>
#include <Cuboid/Platform/DirectX/D3DVertexBuffer.h>

namespace Cuboid
{
	Ref<IndexBuffer> IndexBuffer::Create(uint32_t* indices, uint32_t count)
	{
		switch(RendererAPI::GetAPI())
		{
		case RendererAPI::API::None: CUBOID_CORE_ERROR("None Currently not suppported! "); break;
		case RendererAPI::API::Opengl: return CreateRef<OpenGLIndexBuffer>(indices, count);
#ifdef WIN32
		case RendererAPI::API::DirectX: return CreateRef<D3DIndexBuffer>(indices, count);
#endif
		}
		return nullptr;
	}

	///////////////////Vertex Buffer here!!!!!/////////////////////
	Ref<VertexBuffer> VertexBuffer::Create(void* vertices, uint32_t size)
	{
		switch(RendererAPI::GetAPI())
		{
		case RendererAPI::API::None: CUBOID_CORE_ERROR("None Currently not supported! "); break;
		case RendererAPI::API::Opengl: return  CreateRef<OpenGLVertexBuffer>(vertices, size);
#ifdef WIN32
		case RendererAPI::API::DirectX: return  CreateRef<D3DVertexBuffer>(vertices, size);
#endif
		}
		return nullptr;
	}

	Ref<VertexBuffer> VertexBuffer::Create(uint32_t size)
	{
		switch(RendererAPI::GetAPI())
		{
		case RendererAPI::API::None: CUBOID_CORE_ERROR("None Currently not supported! "); break;
		case RendererAPI::API::Opengl: return  CreateRef<OpenGLVertexBuffer>(size);
#ifdef WIN32
		case RendererAPI::API::DirectX: return  CreateRef<D3DVertexBuffer>(size);
#endif
		}
		return nullptr;
	}

}
