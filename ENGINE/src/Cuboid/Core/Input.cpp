#include "Input.h"
#include "Cuboid/Platform/SystemInput/WindowsInput.h"

namespace Cuboid
{
	Scope<Input> Input::s_Instance = Input::Create();

	Scope<Input> Input::Create()
	{
		return CreateScope<WindowsInput>();
	}
}