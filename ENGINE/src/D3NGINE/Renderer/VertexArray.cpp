#include <d3gpch.h>
#include <D3NGINE/Renderer/RendererAPI.h>
#include <D3NGINE/Platform/OpenGL/OpenGLVertexArray.h>
#include <D3NGINE/Renderer/VertexArray.h>
#include <D3NGINE/Platform/DirectX/Renderer/D3DVertexArray.h>


namespace D3G
{

	Ref<VertexArray> VertexArray::Create()
	{
		switch(RendererAPI::GetAPI())
		{
			case RendererAPI::API::None: 	D3G_CORE_ERROR("No Render API"); break;
			case RendererAPI::API::Opengl: return CreateRef<OpenGLVertexArray>();
			case RendererAPI::API::DirectX: return CreateRef<D3DVertexArray>();
		}

		return nullptr;
	}


}
