#pragma once

#include "WindowsInput.h"
#include "D3NGINE/Core/Application.h"

namespace D3G
{
	bool WindowsInput::IsKeyPressedImpl(KeyCode key)
	{
		if (::GetKeyboardState(m_keys))
		{
			//KeyDown
			if (m_keys[(int)key] & 0x80)
			{
				return true;
			} 
			else 
			{
				
			}

		}
		return false;
	}
	bool WindowsInput::IsMouseButtonPressedImpl(MouseCode button)
	{

		if (::GetKeyboardState(m_keys))
		{
			//KeyDown
			if (m_keys[(int)button] & 0x80)
			{
				return true;
			}
			else
			{
				
			}

		}

		return false;
	}
	std::pair<float, float> WindowsInput::GetMousePositionImpl()
	{
		POINT current_mouse_position = {};
		::GetCursorPos(&current_mouse_position);

		HWND applicationHWND = std::any_cast<HWND>(Application::Get().GetWindow().GetNativeWindow());

		::ScreenToClient(applicationHWND, &current_mouse_position);

		

		return std::pair<float, float>((float)current_mouse_position.x, (float)current_mouse_position.y);
	}
	float WindowsInput::GetMouseXImpl()
	{
		return (float)GetMousePositionImpl().first;
	}
	float WindowsInput::GetMouseYImpl()
	{

		return (float)GetMousePositionImpl().second;
	}
}