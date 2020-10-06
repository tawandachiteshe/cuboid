#pragma once

#include "Cuboid/Core/Window.h"
#include "Cuboid/Renderer/GraphicsContext.h"
#include <string>
#include <SDL.h>

namespace Cuboid
{
	class SDLWindow : public Window
	{
		// Inherited via Window
	public:

		SDLWindow(const WindowProps& props);


		virtual void OnUpdate() override;
		virtual unsigned int GetWidth() const override;
		virtual unsigned int GetHeight() const override;
		virtual void SetVSync(bool enabled) override;
		virtual bool IsVSync() const override;
		virtual std::any GetNativeWindow() const override;

	private:

		virtual void Init(const WindowProps& props);
		virtual void Shutdown();

		struct WindowData
		{

			unsigned int WinHeight =	400;
			unsigned int WinWidth  =	400;
			std::string  title	   =	"default Cuboid application";
			bool		 isVSync   =	false;

		};

		WindowData m_wdWinData;

	private:

		SDL_Window* m_Window = nullptr;
		void* m_pGlContext = nullptr;
		Scope<GraphicsContext> context;

		SDL_Event m_Event;
		


		// Inherited via Window
		virtual void SetEventCallback(const EventCallbackFn& callback) override;


		// Inherited via Window
		virtual void* GetGLContext() const override;

	};
}
