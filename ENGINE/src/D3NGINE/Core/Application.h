#include "Window.h"
#include "LayerStack.h"
#include "D3NGINE/ImGui/ImGuiLayer.h"
#include <SDL_events.h>

#ifndef D3G_APPLICATION_H
#define D3G_APPLICATION_H

namespace D3G
{
	class Application
	{

	public:
		Application();
		virtual ~Application();
		void Run();
		void OnEvent(SDL_Event* event);
		void OnUnHandledEvent(SDL_Event* event);
		void PushLayer(Layer* layer);
		void PushOverLay(Layer* layer);
		void Name();
		inline Window& ApplicationGetWindow() { return *m_Window; }
		inline static Application& Get() { return *m_Instance; }
	private:
		Scope<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		static bool m_Running;
		LayerStack m_LayerStack;
		static Application* m_Instance;
		float m_LastTime;

	};

	Application* CreateApplication();
}

#endif
