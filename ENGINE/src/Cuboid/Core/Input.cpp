#include "Input.h"
#include "Cuboid/Platform/SystemInput/WindowsInput.h"
#include "Cuboid/Platform/SystemInput/SDL2Input.h"

namespace Cuboid
{
	Scope<Input> Input::s_Instance = Input::Create();

	Scope<Input> Input::Create()
	{
#ifdef WIN32
		return CreateScope<WindowsInput>();
#endif
        return CreateScope<SDL2Input>();
	}
}