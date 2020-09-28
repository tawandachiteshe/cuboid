#include "d3gpch.h"
#include "Application.h"
#include <D3NGINE/Renderer/Renderer.h>
#include <imgui_impl_sdl.h>

namespace D3G
{

	Application* Application::m_Instance = nullptr;
	bool Application::m_Running = true;
	Application::Application()
	{
		m_Instance = this;
		m_Window = Window::Create();
		m_Window->SetEventCallback(D3G_BIND_EVENT_FN(Application::OnEvent));

		//Renderer::Init();

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
			for (Layer* layer : m_LayerStack)
			{
				layer->OnImGuiRender();
			}
			m_ImGuiLayer->End();

			m_Window->OnUpdate();


		}
	}

	void Application::OnEvent(Event& e)
	{

		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin(); )
		{
			(*--it)->OnEvent(e);
		}

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


