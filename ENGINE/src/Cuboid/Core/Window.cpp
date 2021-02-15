#include <Cuboidpch.h>
#include "Window.h"
#include "Cuboid/Platform/OpenGL/Renderer/OpenGLGraphicsContext.h"
#include <SDL.h>
#include <Cuboid/Renderer/RendererAPI.h>
#include <Cuboid/Renderer/Renderer.h>

#include "Cuboid/Platform/Windowing/SDLWindow.h"
#ifdef WIN32
#include "Cuboid/Platform/Windowing/WindowsWindow.h"
#endif
namespace Cuboid
{
	


	Scope<Window> Window::Create(const WindowProps& props)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::Opengl:
			return CreateScope<SDLWindow>(props);
		case RendererAPI::API::DirectX:
#ifdef WIN32
			return CreateScope<WindowsWindow>(props);
#endif
		case RendererAPI::API::None:
			CUBOID_CORE_ERROR("Platform not yet supported!!!!");
			return nullptr;
		}
		
	}

}

