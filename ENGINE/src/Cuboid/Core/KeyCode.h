#pragma once

#include <stdint.h>
#include <iostream>

namespace Cuboid
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
#define CUBOID_KEY_SPACE           ::Cuboid::Key::Space
#define CUBOID_KEY_APOSTROPHE      ::Cuboid::Key::Apostrophe    /* ' */
#define CUBOID_KEY_COMMA           ::Cuboid::Key::Comma         /* , */
#define CUBOID_KEY_MINUS           ::Cuboid::Key::Minus         /* - */
#define CUBOID_KEY_PERIOD          ::Cuboid::Key::Period        /* . */
#define CUBOID_KEY_SLASH           ::Cuboid::Key::Slash         /* / */
#define CUBOID_KEY_0               ::Cuboid::Key::D0
#define CUBOID_KEY_1               ::Cuboid::Key::D1
#define CUBOID_KEY_2               ::Cuboid::Key::D2
#define CUBOID_KEY_3               ::Cuboid::Key::D3
#define CUBOID_KEY_4               ::Cuboid::Key::D4
#define CUBOID_KEY_5               ::Cuboid::Key::D5
#define CUBOID_KEY_6               ::Cuboid::Key::D6
#define CUBOID_KEY_7               ::Cuboid::Key::D7
#define CUBOID_KEY_8               ::Cuboid::Key::D8
#define CUBOID_KEY_9               ::Cuboid::Key::D9
#define CUBOID_KEY_SEMICOLON       ::Cuboid::Key::Semicolon     /* ; */
#define CUBOID_KEY_EQUAL           ::Cuboid::Key::Equal         /* = */
#define CUBOID_KEY_A               ::Cuboid::Key::A
#define CUBOID_KEY_B               ::Cuboid::Key::B
#define CUBOID_KEY_C               ::Cuboid::Key::C
#define CUBOID_KEY_D               ::Cuboid::Key::D
#define CUBOID_KEY_E               ::Cuboid::Key::E
#define CUBOID_KEY_F               ::Cuboid::Key::F
#define CUBOID_KEY_G               ::Cuboid::Key::G
#define CUBOID_KEY_H               ::Cuboid::Key::H
#define CUBOID_KEY_I               ::Cuboid::Key::I
#define CUBOID_KEY_J               ::Cuboid::Key::J
#define CUBOID_KEY_K               ::Cuboid::Key::K
#define CUBOID_KEY_L               ::Cuboid::Key::L
#define CUBOID_KEY_M               ::Cuboid::Key::M
#define CUBOID_KEY_N               ::Cuboid::Key::N
#define CUBOID_KEY_O               ::Cuboid::Key::O
#define CUBOID_KEY_P               ::Cuboid::Key::P
#define CUBOID_KEY_Q               ::Cuboid::Key::Q
#define CUBOID_KEY_R               ::Cuboid::Key::R
#define CUBOID_KEY_S               ::Cuboid::Key::S
#define CUBOID_KEY_T               ::Cuboid::Key::T
#define CUBOID_KEY_U               ::Cuboid::Key::U
#define CUBOID_KEY_V               ::Cuboid::Key::V
#define CUBOID_KEY_W               ::Cuboid::Key::W
#define CUBOID_KEY_X               ::Cuboid::Key::X
#define CUBOID_KEY_Y               ::Cuboid::Key::Y
#define CUBOID_KEY_Z               ::Cuboid::Key::Z
#define CUBOID_KEY_LEFT_BRACKET    ::Cuboid::Key::LeftBracket   /* [ */
#define CUBOID_KEY_BACKSLASH       ::Cuboid::Key::Backslash     /* \ */
#define CUBOID_KEY_RIGHT_BRACKET   ::Cuboid::Key::RightBracket  /* ] */
#define CUBOID_KEY_GRAVE_ACCENT    ::Cuboid::Key::GraveAccent   /* ` */
#define CUBOID_KEY_WORLD_1         ::Cuboid::Key::World1        /* non-US #1 */
#define CUBOID_KEY_WORLD_2         ::Cuboid::Key::World2        /* non-US #2 */
								  
#define CUBOID_KEY_ESCAPE          ::Cuboid::Key::Escape
#define CUBOID_KEY_ENTER           ::Cuboid::Key::Enter
#define CUBOID_KEY_TAB             ::Cuboid::Key::Tab
#define CUBOID_KEY_BACKSPACE       ::Cuboid::Key::Backspace
#define CUBOID_KEY_INSERT          ::Cuboid::Key::Insert
#define CUBOID_KEY_DELETE          ::Cuboid::Key::Delete
#define CUBOID_KEY_RIGHT           ::Cuboid::Key::Right
#define CUBOID_KEY_LEFT            ::Cuboid::Key::Left
#define CUBOID_KEY_DOWN            ::Cuboid::Key::Down
#define CUBOID_KEY_UP              ::Cuboid::Key::Up
#define CUBOID_KEY_PAGE_UP         ::Cuboid::Key::PageUp
#define CUBOID_KEY_PAGE_DOWN       ::Cuboid::Key::PageDown
#define CUBOID_KEY_HOME            ::Cuboid::Key::Home
#define CUBOID_KEY_END             ::Cuboid::Key::End
#define CUBOID_KEY_CAPS_LOCK       ::Cuboid::Key::CapsLock
#define CUBOID_KEY_SCROLL_LOCK     ::Cuboid::Key::ScrollLock
#define CUBOID_KEY_NUM_LOCK        ::Cuboid::Key::NumLock
#define CUBOID_KEY_PRINT_SCREEN    ::Cuboid::Key::PrintScreen
#define CUBOID_KEY_PAUSE           ::Cuboid::Key::Pause
#define CUBOID_KEY_F1              ::Cuboid::Key::F1
#define CUBOID_KEY_F2              ::Cuboid::Key::F2
#define CUBOID_KEY_F3              ::Cuboid::Key::F3
#define CUBOID_KEY_F4              ::Cuboid::Key::F4
#define CUBOID_KEY_F5              ::Cuboid::Key::F5
#define CUBOID_KEY_F6              ::Cuboid::Key::F6
#define CUBOID_KEY_F7              ::Cuboid::Key::F7
#define CUBOID_KEY_F8              ::Cuboid::Key::F8
#define CUBOID_KEY_F9              ::Cuboid::Key::F9
#define CUBOID_KEY_F10             ::Cuboid::Key::F10
#define CUBOID_KEY_F11             ::Cuboid::Key::F11
#define CUBOID_KEY_F12             ::Cuboid::Key::F12
#define CUBOID_KEY_F13             ::Cuboid::Key::F13
#define CUBOID_KEY_F14             ::Cuboid::Key::F14
#define CUBOID_KEY_F15             ::Cuboid::Key::F15
#define CUBOID_KEY_F16             ::Cuboid::Key::F16
#define CUBOID_KEY_F17             ::Cuboid::Key::F17
#define CUBOID_KEY_F18             ::Cuboid::Key::F18
#define CUBOID_KEY_F19             ::Cuboid::Key::F19
#define CUBOID_KEY_F20             ::Cuboid::Key::F20
#define CUBOID_KEY_F21             ::Cuboid::Key::F21
#define CUBOID_KEY_F22             ::Cuboid::Key::F22
#define CUBOID_KEY_F23             ::Cuboid::Key::F23
#define CUBOID_KEY_F24             ::Cuboid::Key::F24
#define CUBOID_KEY_F25             ::Cuboid::Key::F25
								  
#define CUBOID_KEY_KP_0            ::Cuboid::Key::KP0
#define CUBOID_KEY_KP_1            ::Cuboid::Key::KP1
#define CUBOID_KEY_KP_2            ::Cuboid::Key::KP2
#define CUBOID_KEY_KP_3            ::Cuboid::Key::KP3
#define CUBOID_KEY_KP_4            ::Cuboid::Key::KP4
#define CUBOID_KEY_KP_5            ::Cuboid::Key::KP5
#define CUBOID_KEY_KP_6            ::Cuboid::Key::KP6
#define CUBOID_KEY_KP_7            ::Cuboid::Key::KP7
#define CUBOID_KEY_KP_8            ::Cuboid::Key::KP8
#define CUBOID_KEY_KP_9            ::Cuboid::Key::KP9
#define CUBOID_KEY_KP_DECIMAL      ::Cuboid::Key::KPDecimal
#define CUBOID_KEY_KP_DIVIDE       ::Cuboid::Key::KPDivide
#define CUBOID_KEY_KP_MULTIPLY     ::Cuboid::Key::KPMultiply
#define CUBOID_KEY_KP_SUBTRACT     ::Cuboid::Key::KPSubtract
#define CUBOID_KEY_KP_ADD          ::Cuboid::Key::KPAdd
#define CUBOID_KEY_KP_ENTER        ::Cuboid::Key::KPEnter
#define CUBOID_KEY_KP_EQUAL        ::Cuboid::Key::KPEqual
								  
#define CUBOID_KEY_LEFT_SHIFT      ::Cuboid::Key::LeftShift
#define CUBOID_KEY_LEFT_CONTROL    ::Cuboid::Key::LeftControl
#define CUBOID_KEY_LEFT_ALT        ::Cuboid::Key::LeftAlt
#define CUBOID_KEY_LEFT_SUPER      ::Cuboid::Key::LeftSuper
#define CUBOID_KEY_RIGHT_SHIFT     ::Cuboid::Key::RightShift
#define CUBOID_KEY_RIGHT_CONTROL   ::Cuboid::Key::RightControl
#define CUBOID_KEY_RIGHT_ALT       ::Cuboid::Key::RightAlt
#define CUBOID_KEY_RIGHT_SUPER     ::Cuboid::Key::RightSuper
#define CUBOID_KEY_MENU            ::Cuboid::Key::Menu

