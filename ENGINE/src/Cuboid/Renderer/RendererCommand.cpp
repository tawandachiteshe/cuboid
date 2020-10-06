#include "RendererCommand.h"
#include <Cuboid/Platform/OpenGL/Renderer/OpenGLRendererAPI.h>

namespace Cuboid
{
	Scope<RendererAPI> RenderCommand::s_RendererAPI = RendererAPI::Create();
}
