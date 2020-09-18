#pragma once

#include "D3NGINE/Core/Input.h"
#include <SDL.h>

namespace D3G
{
	class WindowsInput : public Input
	{
	protected:
		virtual bool IsKeyPressedImpl(KeyCode key) override;
		virtual bool IsMouseButtonPressedImpl(MouseCode button) override;
		virtual std::pair<float, float> GetMousePositionImpl() override;
		virtual float GetMouseXImpl() override;
		virtual float GetMouseYImpl() override;

	private:
		SDL_Event m_Event;

	};
}
