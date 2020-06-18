typedef void *SDL_GLContext;
typedef struct SDL_Window SDL_Window;
typedef union SDL_Event SDL_Event;

#ifndef D3G_UTILS_WINDOW_H
#define D3G_UTILS_WINDOW_H
#include <D3NGINE/Renderer/GraphicsContext.h>

namespace D3G
{

	struct WinProps
	{
		std::string title;
		int WinWidth;
		int WinHeight;
		bool Vsync;
	};

	class Window
	{
	public:
		static Scope<Window> Create(const WinProps& props = { "D3NGINE", 1278, 600, true });
		Window(const WinProps& props = { "D3NGINE", 1278, 600, true });
		void Init(const WinProps& props);
		bool OnUpdate() const;

		inline unsigned int GetWidth() const { return m_WinData.WinWidth; }
		inline unsigned int GetHeight() const { return m_WinData.WinHeight; }
		inline SDL_Window* GetWindow() const { return window; }
		static SDL_Event* GetEvents();
		SDL_Event* GetUnHandledEvents();

		bool IsRunning = true;
		void ShutDown();

		bool IsVsync() const;

		void SetVsync(bool enabled);

		bool OnEvent(SDL_Event* e) const;
		int gladStatus = 0;
		inline int GetGladStatus() { return gladStatus; }
		inline void* GetGLContext() { return m_GlContext; }

		~Window();

	private:
		Scope<GraphicsContext> context;
		SDL_Window* window;
		static SDL_Event m_Event;
		void* m_GlContext = nullptr;
		WinProps m_WinData;
	};



}


#endif
