#include <Cuboid/Renderer/RendererAPI.h>


#ifndef CUBOID_OPENGLRENDERER_H
#define CUBOID_OPENGLRENDERER_H
namespace Cuboid
{
	class OpenGLRendererAPI : public RendererAPI
	{
	public:

		virtual void Init() override;
		virtual void SetClearColor(const glm::vec4& clearColor) override;
		virtual void Clear() override;
		virtual void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) override;
		//note 0x0004 is equal to GL_TRIANGLES
		virtual void DrawIndexed(const Ref<VertexArray>& vertexArray, uint32_t indexCount = 0, uint32_t mode = 0x0004) override;
		virtual ~OpenGLRendererAPI();
	};

}

#endif
