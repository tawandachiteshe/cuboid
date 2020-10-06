#pragma once

#include "Cuboid/Core/Window.h"

namespace Cuboid
{

	class WindowsWindow : public Window
	{
	private:

		struct WindowData
		{
			std::string Title;
			unsigned int Width, Height;
			bool VSync;

			EventCallbackFn EventCallback;
		};

		static Ref<WindowData> m_Data;

		HWND m_Hwnd;
		WNDCLASSEX wc;

		MSG m_Msg;

		Scope<GraphicsContext> context;

		void Init(const WindowProps& props);
		void ShutDown();

		static LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

	public:

		WindowsWindow(const WindowProps& props);
		
		static Ref<WindowData>& GetWindowData() { return m_Data; }

		virtual void OnUpdate() override;
		virtual unsigned int GetWidth() const override;
		virtual unsigned int GetHeight() const override;
		virtual void SetEventCallback(const EventCallbackFn& callback) { m_Data->EventCallback = callback; }
		virtual void SetVSync(bool enabled) override;
		virtual bool IsVSync() const override;
		virtual std::any GetNativeWindow() const override;
		virtual void* GetGLContext() const override;

		~WindowsWindow();
	};

}