#include "RendererCommand.h"
#include <D3NGINE/Platform/OpenGL/Renderer/OpenGLRendererAPI.h>

namespace D3G
{
	Scope<RendererAPI> RenderCommand::s_RendererAPI = RendererAPI::Create();
}
