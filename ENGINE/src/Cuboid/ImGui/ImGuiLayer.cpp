#include "ImGuiLayer.h"
#include <imgui.h>
#include "Cuboid/Core/Application.h"
#include "glad/glad.h"
#include <imgui_impl_sdl.h>
#include <imgui_impl_opengl3.h>
#include <Cuboid/Renderer/RendererAPI.h>
#include <imgui_impl_dx11.h>
#include <Cuboid/Platform/DirectX/Renderer/D3DGraphicsContext.h>
#include <SDL.h>
#include <imgui_impl_win32.h>
#include "Cuboid/Platform/DirectX/Renderer/InitializeD3Devices.h"
#include "ImGuiDock.h"



namespace Cuboid
{

	ImGuiLayer::ImGuiLayer():
				Layer("Imgui")
	{
	}


	ImGuiLayer::~ImGuiLayer()
	{
		//TODO: Create shut down method 
		ImGui_ImplDX11_Shutdown();
		ImGui_ImplWin32_Shutdown();
		ImGui::DestroyContext();
	}

	void ImGuiLayer::OnAttach()
	{

		IMGUI_CHECKVERSION();
		

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

            ImGui_ImplSDL2_InitForOpenGL(std::any_cast<SDL_Window*>(app.GetWindow().GetNativeWindow()),
                                         app.GetWindow().GetGLContext());
            ImGui_ImplOpenGL3_Init("#version 120");
        }
		else if (RendererAPI::GetAPI() == RendererAPI::API::DirectX)
		{
			ImGui_ImplWin32_EnableDpiAwareness();
			ImGui_ImplWin32_Init(std::any_cast<HWND>(app.GetWindow().GetNativeWindow()));
			ImGui_ImplDX11_Init(GraphicsEngine()->GetDevice(), GraphicsEngine()->GetContext());

		}

		io.DisplaySize = ImVec2((float)app.GetWindow().GetWidth(), (float)app.GetWindow().GetHeight());
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
			ImGui_ImplSDL2_NewFrame(std::any_cast<SDL_Window*>(app.GetWindow().GetNativeWindow()));
			
		} else if(RendererAPI::GetAPI() == RendererAPI::API::DirectX)
		{
			ImGui_ImplDX11_NewFrame();
			ImGui_ImplWin32_NewFrame();

		}

		ImGui::NewFrame();
		
		
		
	}

	void ImGuiLayer::End()
	{
		Application& app = Application::Get();
		ImGuiIO& io = ImGui::GetIO();
		io.DisplaySize = ImVec2((float)app.GetWindow().GetWidth(),(float)app.GetWindow().GetHeight());
		
		ImGui::Render();

		if(RendererAPI::GetAPI() == RendererAPI::API::Opengl)
		{
			
			glViewport(0, 0, (int)io.DisplaySize.x, (int)io.DisplaySize.y);
			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
			

			if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
			{
				SDL_Window* backup_current_window = SDL_GL_GetCurrentWindow();
				SDL_GLContext backup_current_context = SDL_GL_GetCurrentContext();
				
				SDL_GL_MakeCurrent(backup_current_window, backup_current_context);
			}
			
		}
		else if (RendererAPI::GetAPI() == RendererAPI::API::DirectX)
		{

			ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

		}

		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
		}


		
	}

	void ImGuiLayer::OnImGuiRender()
	{
		

		ImGui::Begin("dasd");

		ImGui::End();
		//ImGui::ShowDemoWindow(&show);

	}


	void ImGuiLayer::OnEvent(Event& event)
	{

	}

}
