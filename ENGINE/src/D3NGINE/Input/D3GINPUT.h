#include "Input.h"

#ifndef D3GINPUT_H
#define D3GINPUT_H

namespace D3G
{
	class D3GINPUT : public Input
	{
	public:
		static std::string ToString();
	protected:

		static int m_KeyCode;
		virtual bool IsKeyPressedImpl(int KeyCode) override;
		virtual bool IsKeyDownImpl(int KeyCode) override;
		virtual bool IsKeyReleasedImpl(int KeyCode) override;

		virtual bool IsMouseKeyPressedImpl(int KeyCode) override;
		virtual bool IsMouseKeyDownImpl(int KeyCode) override;
		virtual bool IsMouseKeyReleasedImpl(int KeyCode) override;

		virtual int GetMouseXImpl() override;
		virtual int GetMouseYImpl() override;
	};

}

#endif


