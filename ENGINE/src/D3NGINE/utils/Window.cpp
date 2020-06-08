#include "Window.h"
#include "D3NGINE/Platform/OpenGL/Renderer/OpenGLGraphicsContext.h"
#include <SDL.h>
#include <D3NGINE/Renderer/RendererAPI.h>
#include <D3NGINE/Renderer/Renderer.h>

namespace D3G
{
	SDL_Event Window::m_Event;
	Window::Window(const WinProps& props)
	{
		Init(props);
	}

	Window* Window::Create(const WinProps& props)
	{
		return new Window(props);
	}

	void Window::Init(const WinProps& props)
	{
		m_WinData.title     =	props.title;
		m_WinData.WinHeight =	props.WinHeight;
		m_WinData.WinWidth  =	props.WinWidth;

		SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_GAMECONTROLLER);



		SDL_WindowFlags window_flags = (SDL_WindowFlags)(SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);
		window = SDL_CreateWindow(props.title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, props.WinWidth, props.WinHeight, window_flags);
		context = GraphicsContext::Create(window);
		context->Init();
        if(Renderer::GetAPI() == RendererAPI::API::Opengl) {
            m_GlContext = static_cast<OpenGLGraphicsContext*>(context.get())->GetContext();
        }
		SDL_Renderer* renderer = SDL_CreateRenderer(window, -1,SDL_RENDERER_ACCELERATED);
		IsRunning = true;
		SetVsync(true);

	}


	void Window::SetVsync(bool enabled)
	{
		context->SetVsync(enabled);
		m_WinData.Vsync = enabled;

	}


	bool Window::IsVsync() const 
	{
		return m_WinData.Vsync;
	}

	void Window::ShutDown()
	{
		SDL_DestroyWindow(window);
		SDL_Quit();
	}


	bool Window::OnUpdate() const
	{
		context->SwapBuffers();
		return SDL_PollEvent(&m_Event) != 0;
	}
	bool Window::OnEvent(SDL_Event& event) const 
	{
		bool shouldClose = true;
		if (event.type == SDL_QUIT)
			shouldClose = false;

		if (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_CLOSE && event.window.windowID == SDL_GetWindowID(GetWindow()))
			shouldClose = false;
		return shouldClose;
	}
	SDL_Event* Window::GetEvents()
	{
		return &m_Event;
	}

	Window::~Window()
	{
		ShutDown();
	}
}

