#include "D3GINPUT.h"
#include "SDL_events.h"
#include "D3NGINE/Application.h"

namespace D3G{

	Scope<Input> Input::m_InputInstance = CreateScope<D3GINPUT>();

	int D3GINPUT::m_KeyCode = 0;

	bool D3GINPUT::IsKeyPressedImpl(SDL_Keycode KeyCode)
	{
		auto event = Application::Get().ApplicationGetWindow().GetEvents();
		if (event->key.state == SDL_PRESSED)
		{
			if (event->key.keysym.scancode == SDL_GetScancodeFromKey(KeyCode) && event->key.repeat == 0)
			{
				m_KeyCode = KeyCode;
				return true;
			}
		}

		return false;
	}

	bool D3GINPUT::IsKeyDownImpl(SDL_Keycode KeyCode)
	{
		auto event = Application::Get().ApplicationGetWindow().GetEvents();
		if (event->key.state == SDL_PRESSED)
		{
			if (event->key.keysym.scancode == SDL_GetScancodeFromKey(KeyCode))
			{
				m_KeyCode = KeyCode;
				return true;
			}
		}

		return false;
	}


	bool D3GINPUT::IsKeyReleasedImpl(SDL_Keycode KeyCode)
	{
		auto event = Application::Get().ApplicationGetWindow().GetEvents();
		if (event->key.state == SDL_PRESSED)
		{
			if (event->key.keysym.scancode == SDL_GetScancodeFromKey(KeyCode) && event->key.repeat <= 0)
			{
				m_KeyCode = KeyCode;
				return true;
			}
		}

		return false;
	}


	int D3GINPUT::GetMouseXImpl()
	{
		auto event = Application::Get().ApplicationGetWindow().GetEvents();
		if (event->motion.type == SDL_MOUSEMOTION)
		{
			return event->motion.x;
		}
		return event->button.x;
	}

	int D3GINPUT::GetMouseYImpl()
	{
		auto event = Application::Get().ApplicationGetWindow().GetEvents();
		if (event->motion.type == SDL_MOUSEMOTION)
		{
			return event->motion.y;
		}
		return event->button.y;
	}

	bool D3GINPUT::IsMouseKeyPressedImpl(int KeyCode)
	{
		auto event = Application::Get().ApplicationGetWindow().GetEvents();
		if (event->button.state == SDL_PRESSED)
		{
			if (event->button.button == KeyCode)
			{

				m_KeyCode = event->button.button;
				return true;
			}
		}
		return false;
	}
	bool D3GINPUT::IsMouseKeyDownImpl(int KeyCode)
	{
		auto event = Application::Get().ApplicationGetWindow().GetEvents();
		if (event->button.state == SDL_PRESSED)
		{
			if (event->button.button == KeyCode && event->button.clicks <= 1)
			{
				m_KeyCode = event->button.button;
				return true;
			}

		}
		return false;
	}

	bool D3GINPUT::IsMouseKeyReleasedImpl(int KeyCode)
	{
		auto event = Application::Get().ApplicationGetWindow().GetEvents();
		if (event->button.state == SDL_RELEASED)
		{
			if (event->button.button == KeyCode)
			{
				m_KeyCode = event->button.button;
				return true;
			}

		}
		return false;
	}


	std::string D3GINPUT::ToString()
	{
		return SDL_GetKeyName(m_KeyCode);
	}
}
