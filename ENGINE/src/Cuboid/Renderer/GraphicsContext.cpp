#include <Cuboidpch.h>
#include <Cuboid/Renderer/RendererAPI.h>
#include "Cuboid/Platform/OpenGL/Renderer/OpenGLGraphicsContext.h"
#include <Cuboid/Renderer/GraphicsContext.h>
#include <Cuboid/Platform/DirectX/Renderer/D3DGraphicsContext.h>
#include <SDL.h>

namespace Cuboid
{


	Scope<GraphicsContext> GraphicsContext::Create(std::any window)
	{
		switch (RendererAPI::GetAPI())
		{
			case RendererAPI::API::None:    CUBOID_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
			case RendererAPI::API::Opengl:  return CreateScope<OpenGLGraphicsContext>(std::any_cast<SDL_Window*>(window));
			case RendererAPI::API::DirectX: return CreateScope<D3DGraphicsContext>(std::any_cast<HWND>(window));
		}

		CUBOID_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

} /* namespace Cuboid */
