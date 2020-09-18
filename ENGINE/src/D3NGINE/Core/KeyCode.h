#pragma once

#include <stdint.h>
#include <iostream>

namespace D3G
{
	

	typedef enum class KeyCode : uint16_t
	{
		// From glfw3.h
		Space = 32,
		Apostrophe = 39, /* ' */
		Comma = 44, /* , */
		Minus = 45, /* - */
		Period = 46, /* . */
		Slash = 47, /* / */

		D0 = 48, /* 0 */
		D1 = 49, /* 1 */
		D2 = 50, /* 2 */
		D3 = 51, /* 3 */
		D4 = 52, /* 4 */
		D5 = 53, /* 5 */
		D6 = 54, /* 6 */
		D7 = 55, /* 7 */
		D8 = 56, /* 8 */
		D9 = 57, /* 9 */

		Semicolon = 59, /* ; */
		Equal = 61, /* = */

		A = 65,
		B = 66,
		C = 67,
		D = 68,
		E = 69,
		F = 70,
		G = 71,
		H = 72,
		I = 73,
		J = 74,
		K = 75,
		L = 76,
		M = 77,
		N = 78,
		O = 79,
		P = 80,
		Q = 81,
		R = 82,
		S = 83,
		T = 84,
		U = 85,
		V = 86,
		W = 87,
		X = 88,
		Y = 89,
		Z = 90,

		LeftBracket = 91,  /* [ */
		Backslash = 92,  /* \ */
		RightBracket = 93,  /* ] */
		GraveAccent = 96,  /* ` */

		World1 = 161, /* non-US #1 */
		World2 = 162, /* non-US #2 */

		/* Function keys */
		Escape = 256,
		Enter = 257,
		Tab = 258,
		Backspace = 259,
		Insert = 260,
		Delete = 261,
		Right = 262,
		Left = 263,
		Down = 264,
		Up = 265,
		PageUp = 266,
		PageDown = 267,
		Home = 268,
		End = 269,
		CapsLock = 280,
		ScrollLock = 281,
		NumLock = 282,
		PrintScreen = 283,
		Pause = 284,
		F1 = 290,
		F2 = 291,
		F3 = 292,
		F4 = 293,
		F5 = 294,
		F6 = 295,
		F7 = 296,
		F8 = 297,
		F9 = 298,
		F10 = 299,
		F11 = 300,
		F12 = 301,
		F13 = 302,
		F14 = 303,
		F15 = 304,
		F16 = 305,
		F17 = 306,
		F18 = 307,
		F19 = 308,
		F20 = 309,
		F21 = 310,
		F22 = 311,
		F23 = 312,
		F24 = 313,
		F25 = 314,

		/* Keypad */
		KP0 = 320,
		KP1 = 321,
		KP2 = 322,
		KP3 = 323,
		KP4 = 324,
		KP5 = 325,
		KP6 = 326,
		KP7 = 327,
		KP8 = 328,
		KP9 = 329,
		KPDecimal = 330,
		KPDivide = 331,
		KPMultiply = 332,
		KPSubtract = 333,
		KPAdd = 334,
		KPEnter = 335,
		KPEqual = 336,

		LeftShift = 340,
		LeftControl = 341,
		LeftAlt = 342,
		LeftSuper = 343,
		RightShift = 344,
		RightControl = 345,
		RightAlt = 346,
		RightSuper = 347,
		Menu = 348
	} Key;

	inline std::ostream& operator<<(std::ostream& os, KeyCode keyCode)
	{
		os << static_cast<int32_t>(keyCode);
		return os;
	}
}

// From glfw3.h
#define D3G_KEY_SPACE           ::D3G::Key::Space
#define D3G_KEY_APOSTROPHE      ::D3G::Key::Apostrophe    /* ' */
#define D3G_KEY_COMMA           ::D3G::Key::Comma         /* , */
#define D3G_KEY_MINUS           ::D3G::Key::Minus         /* - */
#define D3G_KEY_PERIOD          ::D3G::Key::Period        /* . */
#define D3G_KEY_SLASH           ::D3G::Key::Slash         /* / */
#define D3G_KEY_0               ::D3G::Key::D0
#define D3G_KEY_1               ::D3G::Key::D1
#define D3G_KEY_2               ::D3G::Key::D2
#define D3G_KEY_3               ::D3G::Key::D3
#define D3G_KEY_4               ::D3G::Key::D4
#define D3G_KEY_5               ::D3G::Key::D5
#define D3G_KEY_6               ::D3G::Key::D6
#define D3G_KEY_7               ::D3G::Key::D7
#define D3G_KEY_8               ::D3G::Key::D8
#define D3G_KEY_9               ::D3G::Key::D9
#define D3G_KEY_SEMICOLON       ::D3G::Key::Semicolon     /* ; */
#define D3G_KEY_EQUAL           ::D3G::Key::Equal         /* = */
#define D3G_KEY_A               ::D3G::Key::A
#define D3G_KEY_B               ::D3G::Key::B
#define D3G_KEY_C               ::D3G::Key::C
#define D3G_KEY_D               ::D3G::Key::D
#define D3G_KEY_E               ::D3G::Key::E
#define D3G_KEY_F               ::D3G::Key::F
#define D3G_KEY_G               ::D3G::Key::G
#define D3G_KEY_H               ::D3G::Key::H
#define D3G_KEY_I               ::D3G::Key::I
#define D3G_KEY_J               ::D3G::Key::J
#define D3G_KEY_K               ::D3G::Key::K
#define D3G_KEY_L               ::D3G::Key::L
#define D3G_KEY_M               ::D3G::Key::M
#define D3G_KEY_N               ::D3G::Key::N
#define D3G_KEY_O               ::D3G::Key::O
#define D3G_KEY_P               ::D3G::Key::P
#define D3G_KEY_Q               ::D3G::Key::Q
#define D3G_KEY_R               ::D3G::Key::R
#define D3G_KEY_S               ::D3G::Key::S
#define D3G_KEY_T               ::D3G::Key::T
#define D3G_KEY_U               ::D3G::Key::U
#define D3G_KEY_V               ::D3G::Key::V
#define D3G_KEY_W               ::D3G::Key::W
#define D3G_KEY_X               ::D3G::Key::X
#define D3G_KEY_Y               ::D3G::Key::Y
#define D3G_KEY_Z               ::D3G::Key::Z
#define D3G_KEY_LEFT_BRACKET    ::D3G::Key::LeftBracket   /* [ */
#define D3G_KEY_BACKSLASH       ::D3G::Key::Backslash     /* \ */
#define D3G_KEY_RIGHT_BRACKET   ::D3G::Key::RightBracket  /* ] */
#define D3G_KEY_GRAVE_ACCENT    ::D3G::Key::GraveAccent   /* ` */
#define D3G_KEY_WORLD_1         ::D3G::Key::World1        /* non-US #1 */
#define D3G_KEY_WORLD_2         ::D3G::Key::World2        /* non-US #2 */
								  
#define D3G_KEY_ESCAPE          ::D3G::Key::Escape
#define D3G_KEY_ENTER           ::D3G::Key::Enter
#define D3G_KEY_TAB             ::D3G::Key::Tab
#define D3G_KEY_BACKSPACE       ::D3G::Key::Backspace
#define D3G_KEY_INSERT          ::D3G::Key::Insert
#define D3G_KEY_DELETE          ::D3G::Key::Delete
#define D3G_KEY_RIGHT           ::D3G::Key::Right
#define D3G_KEY_LEFT            ::D3G::Key::Left
#define D3G_KEY_DOWN            ::D3G::Key::Down
#define D3G_KEY_UP              ::D3G::Key::Up
#define D3G_KEY_PAGE_UP         ::D3G::Key::PageUp
#define D3G_KEY_PAGE_DOWN       ::D3G::Key::PageDown
#define D3G_KEY_HOME            ::D3G::Key::Home
#define D3G_KEY_END             ::D3G::Key::End
#define D3G_KEY_CAPS_LOCK       ::D3G::Key::CapsLock
#define D3G_KEY_SCROLL_LOCK     ::D3G::Key::ScrollLock
#define D3G_KEY_NUM_LOCK        ::D3G::Key::NumLock
#define D3G_KEY_PRINT_SCREEN    ::D3G::Key::PrintScreen
#define D3G_KEY_PAUSE           ::D3G::Key::Pause
#define D3G_KEY_F1              ::D3G::Key::F1
#define D3G_KEY_F2              ::D3G::Key::F2
#define D3G_KEY_F3              ::D3G::Key::F3
#define D3G_KEY_F4              ::D3G::Key::F4
#define D3G_KEY_F5              ::D3G::Key::F5
#define D3G_KEY_F6              ::D3G::Key::F6
#define D3G_KEY_F7              ::D3G::Key::F7
#define D3G_KEY_F8              ::D3G::Key::F8
#define D3G_KEY_F9              ::D3G::Key::F9
#define D3G_KEY_F10             ::D3G::Key::F10
#define D3G_KEY_F11             ::D3G::Key::F11
#define D3G_KEY_F12             ::D3G::Key::F12
#define D3G_KEY_F13             ::D3G::Key::F13
#define D3G_KEY_F14             ::D3G::Key::F14
#define D3G_KEY_F15             ::D3G::Key::F15
#define D3G_KEY_F16             ::D3G::Key::F16
#define D3G_KEY_F17             ::D3G::Key::F17
#define D3G_KEY_F18             ::D3G::Key::F18
#define D3G_KEY_F19             ::D3G::Key::F19
#define D3G_KEY_F20             ::D3G::Key::F20
#define D3G_KEY_F21             ::D3G::Key::F21
#define D3G_KEY_F22             ::D3G::Key::F22
#define D3G_KEY_F23             ::D3G::Key::F23
#define D3G_KEY_F24             ::D3G::Key::F24
#define D3G_KEY_F25             ::D3G::Key::F25
								  
#define D3G_KEY_KP_0            ::D3G::Key::KP0
#define D3G_KEY_KP_1            ::D3G::Key::KP1
#define D3G_KEY_KP_2            ::D3G::Key::KP2
#define D3G_KEY_KP_3            ::D3G::Key::KP3
#define D3G_KEY_KP_4            ::D3G::Key::KP4
#define D3G_KEY_KP_5            ::D3G::Key::KP5
#define D3G_KEY_KP_6            ::D3G::Key::KP6
#define D3G_KEY_KP_7            ::D3G::Key::KP7
#define D3G_KEY_KP_8            ::D3G::Key::KP8
#define D3G_KEY_KP_9            ::D3G::Key::KP9
#define D3G_KEY_KP_DECIMAL      ::D3G::Key::KPDecimal
#define D3G_KEY_KP_DIVIDE       ::D3G::Key::KPDivide
#define D3G_KEY_KP_MULTIPLY     ::D3G::Key::KPMultiply
#define D3G_KEY_KP_SUBTRACT     ::D3G::Key::KPSubtract
#define D3G_KEY_KP_ADD          ::D3G::Key::KPAdd
#define D3G_KEY_KP_ENTER        ::D3G::Key::KPEnter
#define D3G_KEY_KP_EQUAL        ::D3G::Key::KPEqual
								  
#define D3G_KEY_LEFT_SHIFT      ::D3G::Key::LeftShift
#define D3G_KEY_LEFT_CONTROL    ::D3G::Key::LeftControl
#define D3G_KEY_LEFT_ALT        ::D3G::Key::LeftAlt
#define D3G_KEY_LEFT_SUPER      ::D3G::Key::LeftSuper
#define D3G_KEY_RIGHT_SHIFT     ::D3G::Key::RightShift
#define D3G_KEY_RIGHT_CONTROL   ::D3G::Key::RightControl
#define D3G_KEY_RIGHT_ALT       ::D3G::Key::RightAlt
#define D3G_KEY_RIGHT_SUPER     ::D3G::Key::RightSuper
#define D3G_KEY_MENU            ::D3G::Key::Menu

