#include <glm/glm.hpp>
#include "VertexArray.h"

#ifndef D3G_RENDERER_RENDERER_API_H
#define D3G_RENDERER_RENDERER_API_H

namespace D3G
{
	class RendererAPI
	{
	public:
		enum class API
		{
			None = 0,
			Opengl = 1
		};

	public:
		virtual void Init() = 0;
		virtual void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) = 0;
		virtual void SetClearColor(const glm::vec4& clearColor) = 0;
		virtual void Clear() = 0;
		//u have to remove this nonsense with the api real enum
		//TODO: MAKE THIS DRAW INDEXED BETTER
		virtual void DrawIndexed(const Ref<VertexArray>& vertexArray, uint32_t indexCount = 0, uint32_t mode = 0x0004) = 0;
		inline static API GetAPI() { return d_API; }
		static Scope<RendererAPI> Create();
		virtual ~RendererAPI() = default;

	private:
		static API d_API;
	};
}

#endif
