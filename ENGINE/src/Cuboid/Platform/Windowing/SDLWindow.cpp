#include "SDLWindow.h"

#include "Cuboid/Renderer/Renderer.h"
#include "Cuboid/Platform/OpenGL/Renderer/OpenGLGraphicsContext.h"

namespace Cuboid
{
	SDLWindow::SDLWindow(const WindowProps& props)
	{
		Init(props);
	}
	void SDLWindow::OnUpdate()
	{
		SDL_PollEvent(&m_Event);
		context->SwapBuffers();
		CUBOID_CORE_DEBUG("Swapping");
	}

	unsigned int SDLWindow::GetWidth() const
	{
		return m_wdWinData.WinWidth;
	}

	unsigned int SDLWindow::GetHeight() const
	{
		return m_wdWinData.WinHeight;
	}

	void SDLWindow::SetVSync(bool enabled)
	{
		m_wdWinData.isVSync = enabled;
	}

	bool SDLWindow::IsVSync() const
	{
		return m_wdWinData.isVSync;
	}

	std::any SDLWindow::GetNativeWindow() const
	{
		return m_Window;
	}

	void SDLWindow::Init(const WindowProps& props)
	{
		m_wdWinData.title = props.Title;
		m_wdWinData.WinHeight = props.Height;
		m_wdWinData.WinWidth = props.Width;

		SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_GAMECONTROLLER);
		SDL_WindowFlags window_flags;

		if (Renderer::GetAPI() == RendererAPI::API::Opengl)
			window_flags = (SDL_WindowFlags)(SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);
		else if (Renderer::GetAPI() == RendererAPI::API::DirectX)
			window_flags = (SDL_WindowFlags)(SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);

		m_Window = SDL_CreateWindow(props.Title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, props.Width, props.Height, window_flags);
		context = GraphicsContext::Create(m_Window);
		context->Init();

		if (Renderer::GetAPI() == RendererAPI::API::Opengl)
			m_pGlContext = dynamic_cast<OpenGLGraphicsContext*>(context.get())->GetContext();

		//SDL_Renderer* renderer = SDL_CreateRenderer(window, -1,SDL_RENDERER_ACCELERATED);
		//IsRunning = true;
		SetVSync(true);
	}

	void SDLWindow::Shutdown()
	{
		SDL_DestroyWindow(m_Window);
		SDL_Quit();
	}

	void SDLWindow::SetEventCallback(const EventCallbackFn& callback)
	{
	}

	void* SDLWindow::GetGLContext() const
	{
		return m_pGlContext;
	}


}