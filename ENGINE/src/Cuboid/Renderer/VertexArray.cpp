#include <Cuboidpch.h>
#include <Cuboid/Renderer/RendererAPI.h>
#include <Cuboid/Platform/OpenGL/OpenGLVertexArray.h>
#include <Cuboid/Renderer/VertexArray.h>
#include <Cuboid/Platform/DirectX/Renderer/D3DVertexArray.h>


namespace Cuboid
{

	Ref<VertexArray> VertexArray::Create()
	{
		switch(RendererAPI::GetAPI())
		{
			case RendererAPI::API::None: 	CUBOID_CORE_ERROR("No Render API"); break;
			case RendererAPI::API::Opengl: return CreateRef<OpenGLVertexArray>();
			case RendererAPI::API::DirectX: return CreateRef<D3DVertexArray>();
		}

		return nullptr;
	}


}
