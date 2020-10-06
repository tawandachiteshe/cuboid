#include "Cuboidpch.h"
#include "Application.h"
#include <Cuboid/Renderer/Renderer.h>
#include <imgui_impl_sdl.h>
#include "Cuboid\ImGui\ImGuiDock.h"
#include "Cuboid\Events\ApplicationEvent.h"
namespace Cuboid
{

	Application* Application::m_Instance = nullptr;
	bool Application::m_Running = true;
	Application::Application(const std::string& name)
	{
		m_Instance = this;
		m_Window = Window::Create(WindowProps(name));
		m_Window->SetEventCallback(CUBOID_BIND_EVENT_FN(Application::OnEvent));

		Renderer::Init();

		m_ImGuiLayer = new ImGuiLayer();
	    PushOverLay(m_ImGuiLayer);


	}


	Application::~Application()
	{

	}

	void Application::Run()
	{
		auto tp1 = std::chrono::system_clock::now();
		auto tp2 = std::chrono::system_clock::now();

		while (m_Running)
		{
			tp2 = std::chrono::system_clock::now();
			std::chrono::duration<float> elapsedTime = tp2 - tp1;
			tp1 = tp2;
			float dt = elapsedTime.count();
			for(Layer* layer : m_LayerStack)
			{

				layer->OnUpdate(dt);
			}


			m_ImGuiLayer->Begin();

			static bool show = false;
			BeginDockSpace(&show);

			for (Layer* layer : m_LayerStack)
			{

				layer->OnImGuiRender();

			}

			EndDockSpace();

			m_ImGuiLayer->End();

			m_Window->OnUpdate();


		}
	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatch(e);

		dispatch.Dispatch<WindowCloseEvent>(CUBOID_BIND_EVENT_FN(Application::OnApplicationClose));

		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin(); )
		{
			(*--it)->OnEvent(e);
		}

	}

	bool Application::OnApplicationClose(Event& event)
	{
		CUBOID_CORE_INFO("Window closed");
		m_Running = false;
		Renderer::ShutDown();

		return true;
	}

	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverLay(Layer* layer)
	{
		m_LayerStack.PushOverLay(layer);
		layer->OnAttach();

	}

}


