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
			for (Layer* layer : m_LayerStack)
			{
				layer->OnImGuiRender();
			}
			m_ImGuiLayer->End();


			bool isPolling = m_Window->OnUpdate();
			SDL_Event* event = m_Window->GetEvents();
			if(isPolling)
			{
				ImGui_ImplSDL2_ProcessEvent(event);
				this->OnEvent(event);
				m_Running = m_Window->OnEvent(event);
			}

			this->OnUnHandledEvent(event);

			int w, h = 0;
			SDL_GetWindowSize(m_Window->GetWindow(), &w, &h);
			Renderer::OnWindowResize((uint32_t)w, (uint32_t)h);

		}
	}

	void Application::OnEvent(SDL_Event* e)
	{

		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin(); )
		{
			(*--it)->OnEvent(e);
		}

	}

    void Application::OnUnHandledEvent(SDL_Event* e)
    {
        for (auto it = m_LayerStack.end(); it != m_LayerStack.begin(); )
        {
            (*--it)->OnUnHandledEvent(e);
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


