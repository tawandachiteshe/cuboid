#pragma once

#include "D3NGINE/Core/Window.h"

namespace D3G
{

	class WindowsWindow : public Window
	{
	private:
		HWND m_Hwnd;
		WNDCLASSEX wc;

		MSG m_Msg;

		Scope<GraphicsContext> context;

		WindowProps m_wdData;

		void Init(const WindowProps& props);
		void ShutDown();

		static LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

	public:

		WindowsWindow(const WindowProps& props);

		virtual void OnUpdate() override;
		virtual unsigned int GetWidth() const override;
		virtual unsigned int GetHeight() const override;
		virtual void SetEventCallback(const EventCallbackFn& callback) override;
		virtual void SetVSync(bool enabled) override;
		virtual bool IsVSync() const override;
		virtual std::any GetNativeWindow() const override;
		virtual void* GetGLContext() const override;

		~WindowsWindow();
	};

}