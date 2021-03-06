typedef void *SDL_GLContext;
typedef struct SDL_Window SDL_Window;
typedef union SDL_Event SDL_Event;

#ifndef CUBOID_UTILS_WINDOW_H
#define CUBOID_UTILS_WINDOW_H
#include <Cuboid/Renderer/GraphicsContext.h>
#include "Cuboid/Events/Event.h"
#include <any>

namespace Cuboid
{
	struct WindowProps
	{
		std::string Title;
		unsigned int Width;
		unsigned int Height;

		WindowProps(const std::string& title = "Cuboid Engine",
			unsigned int width = 1280,
			unsigned int height = 720)
			: Title(title), Width(width), Height(height)
		{
		}
	};

	class Window
	{
	public:

		using EventCallbackFn = std::function<void(Event&)>;
		

		virtual ~Window() = default;

		virtual void OnUpdate() = 0;

		virtual unsigned int GetWidth() const = 0;
		virtual unsigned int GetHeight() const = 0;

		// Window attributes
		virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
		virtual void SetVSync(bool enabled) = 0;
		virtual bool IsVSync() const = 0;

		virtual std::any GetNativeWindow() const = 0;
		virtual void* GetGLContext() const = 0;

		static Scope<Window> Create(const WindowProps& props = WindowProps());
	};
	
}


#endif
