#include <D3NGINE/Renderer/RendererAPI.h>
#include <D3NGINE/Platform/OpenGL/OpenGLVertexArray.h>
#include <D3NGINE/Renderer/VertexArray.h>

namespace D3G
{

	Ref<VertexArray> VertexArray::Create()
	{
		switch(RendererAPI::GetAPI())
		{
			case RendererAPI::API::None: 	D3G_CORE_ERROR("No Render API"); break;
			case RendererAPI::API::Opengl: return CreateRef<OpenGLVertexArray>();
		}

		return nullptr;
	}


}
