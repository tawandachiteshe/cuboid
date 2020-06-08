#include <D3NGINE/Renderer/RendererAPI.h>
#include <D3NGINE/Platform/OpenGL/Renderer/OpenGLRendererAPI.h>


namespace D3G
{
	RendererAPI::API RendererAPI::d_API = RendererAPI::API::Opengl;


	Scope<RendererAPI> RendererAPI::Create()
	{
		switch (d_API)
		{
		case RendererAPI::API::None:    D3G_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::Opengl:  return CreateScope<OpenGLRendererAPI>();
		}

		D3G_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}
