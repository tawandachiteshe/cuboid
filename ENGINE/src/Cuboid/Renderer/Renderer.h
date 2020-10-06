#include "RendererCommand.h"
#include <Cuboid/Renderer/Camera2D.h>
#include <Cuboid/Renderer/Shader.h>
#include <Cuboid/Renderer/VertexArray.h>
#include <glm/glm.hpp>


#ifndef CUBOID_RENDERER_RENDERERER_H
#define CUBOID_RENDERER_RENDERERER_H

namespace Cuboid
{
	class Renderer
	{
		public:
			inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
			Renderer();
			virtual ~Renderer();
			static void Init();
			static void BeginScene(const Camera2D& camera);
			static void EndScene();
			static void Submit(const Ref<VertexArray>& vtxArray,const Ref<Shader>& shader,  const glm::mat4& transform = glm::mat4(1.0f));
			static void OnWindowResize(uint32_t width, uint32_t height);
			static void ShutDown();

		private:

			struct SceneData
			{
				glm::mat4 m_ProjectionViewMatrix;
			};

			static Scope<SceneData> m_SceneData;
	};
}

#endif
