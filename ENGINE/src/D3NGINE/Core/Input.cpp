#include "Input.h"
#include "D3NGINE/Platform/SystemInput/WindowsInput.h"

namespace D3G
{
	Scope<Input> Input::s_Instance = Input::Create();

	Scope<Input> Input::Create()
	{
		return CreateScope<WindowsInput>();
	}
}