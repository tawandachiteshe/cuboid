#include <Cuboid/Renderer/RendererAPI.h>
#include <Cuboid/Renderer/VertexArray.h>

#ifndef CUBOID_RENDERER_RENDERER_COMMAND_H
#define CUBOID_RENDERER_RENDERER_COMMAND_H
namespace Cuboid
{

	class RenderCommand
	{
		public:

			static void Init()
			{
				s_RendererAPI->Init();
			}

			static void SetClearColor(const glm::vec4& clearColor)
			{
				s_RendererAPI->SetClearColor(clearColor);
			}

			static void Clear()
			{
				s_RendererAPI->Clear();

			}

			static void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
			{
				s_RendererAPI->SetViewport(x, y, width, height);
			}

			static void DrawIndexed(const Ref<VertexArray>& vtxArray, uint32_t count = 0, uint32_t mode = 0x0004)
			{
				s_RendererAPI->DrawIndexed(vtxArray, count, mode);
			}

		private:
			static Scope<RendererAPI> s_RendererAPI;

	};

}

#endif
