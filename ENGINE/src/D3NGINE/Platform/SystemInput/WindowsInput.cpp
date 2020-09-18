#pragma once

#include "WindowsInput.h"

namespace D3G
{
	bool WindowsInput::IsKeyPressedImpl(KeyCode key)
	{
		if (SDL_PollEvent(&m_Event)) {



		}
		return false;
	}
	bool WindowsInput::IsMouseButtonPressedImpl(MouseCode button)
	{
		return false;
	}
	std::pair<float, float> WindowsInput::GetMousePositionImpl()
	{
		return std::pair<float, float>();
	}
	float WindowsInput::GetMouseXImpl()
	{
		return 0.0f;
	}
	float WindowsInput::GetMouseYImpl()
	{
		return 0.0f;
	}
}