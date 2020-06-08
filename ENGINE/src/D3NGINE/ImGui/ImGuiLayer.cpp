#include "ImGuiLayer.h"
#include <imgui.h>
#include "D3NGINE/Application.h"
#include "glad/glad.h"
#include <imgui_impl_sdl.h>
#include <imgui_impl_opengl3.h>
#include <D3NGINE/Renderer/RendererAPI.h>
#include <SDL_events.h>

namespace D3G
{

	ImGuiLayer::ImGuiLayer():
				Layer("Imgui")
	{
	}


	ImGuiLayer::~ImGuiLayer()
	{
	}
	void ImGuiLayer::OnAttach()
	{

		Application& app = Application::Get();
		ImGui::SetCurrentContext(ImGui::CreateContext());
		ImGui::StyleColorsClassic();
		ImGuiIO& io = ImGui::GetIO();

		io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
		io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
		io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

		ImGuiStyle& style = ImGui::GetStyle();
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			style.WindowRounding = 0.0f;
			style.Colors[ImGuiCol_WindowBg].w = 1.0f;
		}
        if(RendererAPI::GetAPI() == RendererAPI::API::Opengl) {
            ImGui_ImplSDL2_InitForOpenGL(app.ApplicationGetWindow().GetWindow(),
                                         app.ApplicationGetWindow().GetGLContext());
            ImGui_ImplOpenGL3_Init("#version 120");
        }
		io.DisplaySize = ImVec2((float)app.ApplicationGetWindow().GetWidth(), (float)app.ApplicationGetWindow().GetHeight());
	}

	void ImGuiLayer::OnDetach()
	{
		//TODO: Do some clean up here dawg
	}

	void ImGuiLayer::Begin()
	{
		Application& app = Application::Get();
		if(RendererAPI::GetAPI() == RendererAPI::API::Opengl)
		{
			ImGui_ImplOpenGL3_NewFrame();
		}
		ImGui_ImplSDL2_NewFrame(app.ApplicationGetWindow().GetWindow());
		ImGui::NewFrame();
	}

	void ImGuiLayer::End()
	{
		Application& app = Application::Get();
		ImGuiIO& io = ImGui::GetIO();
		io.DisplaySize = ImVec2((float)app.ApplicationGetWindow().GetWidth(),(float)app.ApplicationGetWindow().GetHeight());
		ImGui::Render();

		if(RendererAPI::GetAPI() == RendererAPI::API::Opengl)
		{

			glViewport(0, 0, (int)io.DisplaySize.x, (int)io.DisplaySize.y);
			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

			if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
			{
				SDL_Window* backup_current_window = SDL_GL_GetCurrentWindow();
				SDL_GLContext backup_current_context = SDL_GL_GetCurrentContext();
				ImGui::UpdatePlatformWindows();
				ImGui::RenderPlatformWindowsDefault();
				SDL_GL_MakeCurrent(backup_current_window, backup_current_context);
			}

		}
	}

	void ImGuiLayer::OnImGuiRender()
	{

		//static bool show = false;
		//ImGui::ShowDemoWindow(&show);

	}


	void ImGuiLayer::OnEvent(SDL_Event& event)
	{

	}

}
