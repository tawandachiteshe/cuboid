#pragma once

#include "Cuboid/Core/Input.h"
#include <SDL.h>

namespace Cuboid
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
		unsigned char m_keys[256] = {};

	};
}
