#include <Cuboid/Renderer/RendererAPI.h>
#include <Cuboid/Platform/OpenGL/Renderer/OpenGLRendererAPI.h>
#ifdef WIN32
#include <Cuboid/Platform/DirectX/Renderer/D3DRendererAPI.h>
#endif

namespace Cuboid
{
	RendererAPI::API RendererAPI::d_API = RendererAPI::API::Opengl;


	Scope<RendererAPI> RendererAPI::Create()
	{
		switch (d_API)
		{
		case RendererAPI::API::None:    CUBOID_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::Opengl:  return CreateScope<OpenGLRendererAPI>();
#ifdef WIN32
		case RendererAPI::API::DirectX:  return CreateScope<D3DRendererAPI>();
#endif
		}

		CUBOID_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}
