#pragma once

#include <stdint.h>
#include <iostream>

namespace D3G
{
	typedef enum class MouseCode : uint16_t
	{
		// From glfw3.h
		Button0 = 0,
		Button1 = 1,
		Button2 = 2,
		Button3 = 3,
		Button4 = 4,
		Button5 = 5,
		Button6 = 6,
		Button7 = 7,

		ButtonLast = Button7,
		ButtonLeft = Button0,
		ButtonRight = Button1,
		ButtonMiddle = Button2
	} Mouse;

	inline std::ostream& operator<<(std::ostream& os, MouseCode mouseCode)
	{
		os << static_cast<int32_t>(mouseCode);
		return os;
	}
}

#define D3G_MOUSE_BUTTON_0      ::D3G::Mouse::Button0
#define D3G_MOUSE_BUTTON_1      ::D3G::Mouse::Button1
#define D3G_MOUSE_BUTTON_2      ::D3G::Mouse::Button2
#define D3G_MOUSE_BUTTON_3      ::D3G::Mouse::Button3
#define D3G_MOUSE_BUTTON_4      ::D3G::Mouse::Button4
#define D3G_MOUSE_BUTTON_5      ::D3G::Mouse::Button5
#define D3G_MOUSE_BUTTON_6      ::D3G::Mouse::Button6
#define D3G_MOUSE_BUTTON_7      ::D3G::Mouse::Button7
#define D3G_MOUSE_BUTTON_LAST   ::D3G::Mouse::ButtonLast
#define D3G_MOUSE_BUTTON_LEFT   ::D3G::Mouse::ButtonLeft
#define D3G_MOUSE_BUTTON_RIGHT  ::D3G::Mouse::ButtonRight
#define D3G_MOUSE_BUTTON_MIDDLE ::D3G::Mouse::ButtonMiddle
