#include <d3gpch.h>
#include "Window.h"
#include "D3NGINE/Platform/OpenGL/Renderer/OpenGLGraphicsContext.h"
#include <SDL.h>
#include <D3NGINE/Renderer/RendererAPI.h>
#include <D3NGINE/Renderer/Renderer.h>

#include "D3NGINE/Platform/Windowing/SDLWindow.h"
#include "D3NGINE/Platform/Windowing/WindowsWindow.h"

namespace D3G
{
	


	Scope<Window> Window::Create(const WindowProps& props)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::Opengl:
			return CreateScope<SDLWindow>(props);
		case RendererAPI::API::DirectX:
			return CreateScope<WindowsWindow>(props);
		case RendererAPI::API::None:
			D3G_CORE_ERROR("Platform not yet supported!!!!");
			return nullptr;
		}
		
	}

}

