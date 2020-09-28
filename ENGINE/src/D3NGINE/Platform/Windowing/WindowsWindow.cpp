#include "WindowsWindow.h"
#include <tchar.h>
#include "D3NGINE/Platform/DirectX/Renderer/InitializeD3Devices.h"
#include <imgui_impl_win32.h>

#include "D3NGINE/Events/ApplicationEvent.h"
#include "D3NGINE/Events/KeyEvent.h"
#include "D3NGINE/Events/MouseEvent.h"

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

namespace D3G
{
	Ref<WindowsWindow::WindowData> WindowsWindow::m_Data = CreateRef<WindowsWindow::WindowData>();

	void WindowsWindow::Init(const WindowProps& props)
	{
		ZeroMemory(&m_Msg, sizeof(m_Msg));

		m_Data->Height = props.Height;
		m_Data->Width = props.Width;

		wc = { sizeof(WNDCLASSEX), CS_CLASSDC, WndProc, 0L, 0L, GetModuleHandle(NULL), NULL, NULL, NULL, NULL, _T(props.Title.c_str()), NULL };
		::RegisterClassEx(&wc);
		m_Hwnd = ::CreateWindow(wc.lpszClassName, _T(props.Title.c_str()), WS_OVERLAPPEDWINDOW, 0, 0, props.Width, props.Height, NULL, NULL, wc.hInstance, NULL);

		D3G_CORE_ASSERT(m_Hwnd, "UNABLE TO CREATE HWND")

		

		::ShowWindow(m_Hwnd, SW_SHOWDEFAULT);
		::UpdateWindow(m_Hwnd);

		context = GraphicsContext::Create(m_Hwnd);
		context->Init();

		
	}

	void WindowsWindow::ShutDown()
	{
		::UnregisterClass(wc.lpszClassName, wc.hInstance);
		::DestroyWindow(m_Hwnd);
	}

	WindowsWindow::WindowsWindow(const WindowProps& props)
	{
		Init(props);
	}


	void WindowsWindow::OnUpdate()
	{

		
		if (::PeekMessage(&m_Msg, NULL, 0U, 0U, PM_REMOVE))
		{
				::TranslateMessage(&m_Msg);
				::DispatchMessage(&m_Msg);
		}
		

		context->SwapBuffers();

	}

	unsigned int WindowsWindow::GetWidth() const
	{
		return m_Data->Width;
	}

	unsigned int WindowsWindow::GetHeight() const
	{
		return m_Data->Height;
	}

	void WindowsWindow::SetVSync(bool enabled)
	{
		m_Data->VSync = enabled;
	}

	bool WindowsWindow::IsVSync() const
	{
		return m_Data->VSync;
	}

	std::any WindowsWindow::GetNativeWindow() const
	{
		return m_Hwnd;
	}

	void* WindowsWindow::GetGLContext() const
	{
		return nullptr;
	}

	WindowsWindow::~WindowsWindow()
	{
		ShutDown();
	}


	

	LRESULT WINAPI WindowsWindow::WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{

		if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
			return true;

		switch (msg)
		{

		case WM_LBUTTONDOWN: case WM_LBUTTONDBLCLK:
		case WM_RBUTTONDOWN: case WM_RBUTTONDBLCLK:
		case WM_MBUTTONDOWN: case WM_MBUTTONDBLCLK:
		case WM_XBUTTONDOWN: case WM_XBUTTONDBLCLK:

		{
			int button = 0;
			if (msg == WM_LBUTTONDOWN || msg == WM_LBUTTONDBLCLK) { button = 0; }
			if (msg == WM_RBUTTONDOWN || msg == WM_RBUTTONDBLCLK) { button = 1; }
			if (msg == WM_MBUTTONDOWN || msg == WM_MBUTTONDBLCLK) { button = 2; }

			MouseButtonPressedEvent mousePressedEvent(static_cast<MouseCode>(button));
			auto& windowData = WindowsWindow::GetWindowData();
			windowData->EventCallback(mousePressedEvent);
		}

			return 0;

		case WM_LBUTTONUP:
		case WM_RBUTTONUP:
		case WM_MBUTTONUP:
		case WM_XBUTTONUP:

		{
			int button = 0;
			if (msg == WM_LBUTTONUP) { button = 0; }
			if (msg == WM_RBUTTONUP) { button = 1; }
			if (msg == WM_MBUTTONUP) { button = 2; }

			MouseButtonReleasedEvent mouseButtonReleasedEvent(static_cast<MouseCode>(button));
			auto& windowData = WindowsWindow::GetWindowData();
			windowData->EventCallback(mouseButtonReleasedEvent);

		}

			return 0;

		case WM_MOUSEWHEEL:
		{
			float mouseWheel = (float)GET_WHEEL_DELTA_WPARAM(wParam) / (float)WHEEL_DELTA;
			MouseScrolledEvent mouseScrolledEvent(mouseWheel, mouseWheel);
			auto& windowData = WindowsWindow::GetWindowData();
			windowData->EventCallback(mouseScrolledEvent);



		}
			
			return 0;

		case WM_KEYDOWN:
		case WM_SYSKEYDOWN:
		{
			KeyPressedEvent keyPressedEvent(static_cast<KeyCode>(wParam), 1);
			auto& windowData = WindowsWindow::GetWindowData();
			windowData->EventCallback(keyPressedEvent);
		}
			return 0;

		case WM_KEYUP:
		case WM_SYSKEYUP:

		{
			KeyReleasedEvent keyReleaseEvent(static_cast<KeyCode>(wParam));
			auto& windowData = WindowsWindow::GetWindowData();
			windowData->EventCallback(keyReleaseEvent);
		}

			return 0;

		case WM_SIZE:
			if (GraphicsEngine()->GetDevice() != NULL && wParam != SIZE_MINIMIZED)
			{

				GraphicsEngine()->CleanupRenderTarget();
				GraphicsEngine()->GetSwapChain()->ResizeBuffers(0, (UINT)LOWORD(lParam), (UINT)HIWORD(lParam), DXGI_FORMAT_UNKNOWN, 0);
				GraphicsEngine()->CreateRenderTarget();

				WindowResizeEvent windowResizeEvent((UINT)LOWORD(lParam), (UINT)HIWORD(lParam));
				auto& windowData = WindowsWindow::GetWindowData();
				windowData->Width = (UINT)LOWORD(lParam);
				windowData->Height = (UINT)HIWORD(lParam);

				windowData->EventCallback(windowResizeEvent);
			}			
			return 0;
		case WM_SYSCOMMAND:
			if ((wParam & 0xfff0) == SC_KEYMENU) // Disable ALT application menu
				return 0;
			break;
		case WM_DESTROY:
		{
			WindowCloseEvent windowClosedEvent;
			auto& windowData = WindowsWindow::GetWindowData();

			windowData->EventCallback(windowClosedEvent);
		}

			::PostQuitMessage(0);
			return 0;


		
		}

		return ::DefWindowProc(hWnd, msg, wParam, lParam);
	}

}

