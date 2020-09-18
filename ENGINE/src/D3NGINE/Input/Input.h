#define G3G_PRESSED			1
#define G3G_RELEASED		0
#define MOUSE_BUTTON_LEFT     1
#define MOUSE_BUTTON_MIDDLE   2
#define MOUSE_BUTTON_RIGHT    3

#ifndef D3G_INPUT_H
#define D3G_INPUT_H

namespace D3G
{

		class Input
		{



		public:

			static bool IsKeyPressed(int KeyCode){ return m_InputInstance->IsKeyPressedImpl(KeyCode); }
			static bool IsKeyDown(int KeyCode) { return m_InputInstance->IsKeyDownImpl(KeyCode); }
			static bool IsKeyReleased(int KeyCode){ return m_InputInstance->IsKeyReleasedImpl(KeyCode); }

			static bool IsMouseKeyPressed(int KeyCode){	return m_InputInstance->IsMouseKeyPressedImpl(KeyCode); }
			static bool IsMouseKeyDown(int KeyCode) {	return m_InputInstance->IsMouseKeyDownImpl(KeyCode); }
			static bool IsMouseKeyReleased(int KeyCode){ return m_InputInstance->IsMouseKeyReleasedImpl(KeyCode); }

			static int GetMouseX() { return m_InputInstance->GetMouseXImpl(); }
			static int GetMouseY() { return m_InputInstance->GetMouseYImpl(); }
			virtual ~Input() = default;

		protected:

			virtual bool IsKeyPressedImpl(int KeyCode) = 0;
			virtual bool IsKeyDownImpl(int KeyCode) = 0;
			virtual bool IsKeyReleasedImpl(int KeyCode) = 0;

			virtual bool IsMouseKeyPressedImpl(int KeyCode) = 0;
			virtual bool IsMouseKeyDownImpl(int KeyCode) = 0;
			virtual bool IsMouseKeyReleasedImpl(int KeyCode) = 0;

			virtual int GetMouseXImpl() = 0;
			virtual int GetMouseYImpl() = 0;

		private:

			static Scope<Input> m_InputInstance;

		};

}

#endif
