#include "Window.h"
#include "LayerStack.h"
#include "Cuboid/ImGui/ImGuiLayer.h"
#include "Cuboid/Events/Event.h"

#ifndef CUBOID_APPLICATION_H
#define CUBOID_APPLICATION_H

namespace Cuboid
{
	class Application
	{

	public:
		Application(const std::string& name = "Cuboid Engine");
		virtual ~Application();
		void Run();
		void OnEvent(Event& event);

		bool OnApplicationClose(Event& event);

		void PushLayer(Layer* layer);
		void PushOverLay(Layer* layer);
		void Name();
		Window& GetWindow() { return *m_Window; }
		static Application& Get() { return *m_Instance; }

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

