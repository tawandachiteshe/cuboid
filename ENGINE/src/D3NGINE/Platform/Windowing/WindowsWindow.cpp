#include "WindowsWindow.h"
#include <tchar.h>
#include "D3NGINE/Platform/DirectX/Renderer/InitializeD3Devices.h"
#include <imgui_impl_win32.h>


extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

namespace D3G
{

	void WindowsWindow::Init(const WindowProps& props)
	{
		ZeroMemory(&m_Msg, sizeof(m_Msg));
		m_wdData.Height = props.Height;
		m_wdData.Width = props.Width;

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
		return m_wdData.Width;
	}

	unsigned int WindowsWindow::GetHeight() const
	{
		return m_wdData.Height;
	}

	void WindowsWindow::SetEventCallback(const EventCallbackFn& callback)
	{
	}

	void WindowsWindow::SetVSync(bool enabled)
	{
	}

	bool WindowsWindow::IsVSync() const
	{
		return false;
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
		case WM_SIZE:
			if (GraphicsEngine()->GetDevice() != NULL && wParam != SIZE_MINIMIZED)
			{

				D3G_CORE_DEBUG("{0} size", (UINT)LOWORD(lParam));

				GraphicsEngine()->CleanupRenderTarget();
				GraphicsEngine()->GetSwapChain()->ResizeBuffers(0, (UINT)LOWORD(lParam), (UINT)HIWORD(lParam), DXGI_FORMAT_UNKNOWN, 0);
				GraphicsEngine()->CreateRenderTarget();
			}			
			return 0;
		case WM_SYSCOMMAND:
			if ((wParam & 0xfff0) == SC_KEYMENU) // Disable ALT application menu
				return 0;
			break;
		case WM_DESTROY:
			::PostQuitMessage(0);
			return 0;
		}

		return ::DefWindowProc(hWnd, msg, wParam, lParam);
	}

}

