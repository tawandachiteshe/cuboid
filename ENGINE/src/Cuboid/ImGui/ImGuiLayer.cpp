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
#include "Cuboid/Platform/DirectX/InitializeD3Devices.h"
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
#ifdef WIN32
		ImGui_ImplDX11_Shutdown();
		ImGui_ImplWin32_Shutdown();
#endif
		ImGui::DestroyContext();
	}

	void ImGuiLayer::OnAttach()
	{

		IMGUI_CHECKVERSION();
		

		Application& app = Application::Get();


		ImGui::SetCurrentContext(ImGui::CreateContext());
		ImGui::StyleColorsDark();
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


		io.Fonts->AddFontFromFileTTF("res/fonts/DroidSans-Bold.ttf", 14.0f);
		io.FontDefault = io.Fonts->AddFontFromFileTTF("res/fonts/DroidSans.ttf", 14.0f);
		SetDarkThemeColors();

        if(RendererAPI::GetAPI() == RendererAPI::API::Opengl) {

            ImGui_ImplSDL2_InitForOpenGL(std::any_cast<SDL_Window*>(app.GetWindow().GetNativeWindow()),
                                         app.GetWindow().GetGLContext());
            ImGui_ImplOpenGL3_Init("#version 300 es");
        }
#ifdef WIN32
		else if (RendererAPI::GetAPI() == RendererAPI::API::DirectX)
		{
			ImGui_ImplWin32_EnableDpiAwareness();
			ImGui_ImplWin32_Init(std::any_cast<HWND>(app.GetWindow().GetNativeWindow()));
			ImGui_ImplDX11_Init(GraphicsEngine()->GetDevice().Get(), GraphicsEngine()->GetContext().Get());

		}
#endif

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
#ifdef WIN32
			ImGui_ImplDX11_NewFrame();
			ImGui_ImplWin32_NewFrame();
#endif

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
#ifdef WIN32
			ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
#endif

		}

		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
		}


		
	}

	void ImGuiLayer::OnImGuiRender()
	{
		

	}


	void ImGuiLayer::OnEvent(Event& event)
	{		
		if (m_bBlockImGuiEvents)
		{
			ImGuiIO& io = ImGui::GetIO();
			event.Handled |= event.IsInCategory(EventCategoryMouse) & io.WantCaptureMouse;
			event.Handled |= event.IsInCategory(EventCategoryKeyboard) & io.WantCaptureKeyboard;
		}

		//temp
        SDL_Event sdl_event;
		SDL_PollEvent(&sdl_event);
        ImGui_ImplSDL2_ProcessEvent(&sdl_event);
/*
        if (sdl_event.type == SDL_QUIT)
            done = true;
        if (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_CLOSE && event.window.windowID == SDL_GetWindowID(window))
            done = true;
*/
	}

	void ImGuiLayer::SetDarkThemeColors()
	{
		auto& colors = ImGui::GetStyle().Colors;
		colors[ImGuiCol_WindowBg] = ImVec4{ 0.1f, 0.105f, 0.11f, 1.0f };

		//headers
		colors[ImGuiCol_Header] = ImVec4{ 0.2f, 0.205f, 0.21f, 1.0f };
		colors[ImGuiCol_HeaderHovered] = ImVec4{ 0.3f, 0.305f, 0.31f, 1.0f };
		colors[ImGuiCol_HeaderActive] = ImVec4{ 0.15f, 0.150f, 0.151f, 1.0f };

		//Buttons
		colors[ImGuiCol_Button] = ImVec4{ 0.2f, 0.205f, 0.21f, 1.0f };
		colors[ImGuiCol_ButtonHovered] = ImVec4{ 0.3f, 0.305f, 0.31f, 1.0f };
		colors[ImGuiCol_ButtonActive] = ImVec4{ 0.15f, 0.150f, 0.151f, 1.0f };

		//FrameBG
		colors[ImGuiCol_FrameBg] = ImVec4{ 0.2f, 0.205f, 0.21f, 1.0f };
		colors[ImGuiCol_FrameBgHovered] = ImVec4{ 0.3f, 0.305f, 0.31f, 1.0f };
		colors[ImGuiCol_FrameBgActive] = ImVec4{ 0.15f, 0.150f, 0.151f, 1.0f };

		//Tabs
		colors[ImGuiCol_Tab] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
		colors[ImGuiCol_TabHovered] = ImVec4{ 0.38f, 0.3805f, 0.381f, 1.0f };
		colors[ImGuiCol_TabActive] = ImVec4{ 0.28f, 0.2805f, 0.281f, 1.0f };
		colors[ImGuiCol_TabUnfocused] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
		colors[ImGuiCol_TabUnfocused] = ImVec4{ 0.2f, 0.205f, 0.21f, 1.0f };

		//docking
		colors[ImGuiCol_DockingPreview] = colors[ImGuiCol_Header];
		colors[ImGuiCol_DockingEmptyBg] = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);

		//titles
		colors[ImGuiCol_TitleBg]			= ImVec4{ 0.1f, 0.1505f, 0.151f, 1.0f };
		colors[ImGuiCol_TitleBgActive]		= ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
		colors[ImGuiCol_TitleBgCollapsed]	= ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };


	}

}
