#include <Cuboidpch.h>

#include <Cuboid/Platform/OpenGL/Renderer/OpenGLRendererAPI.h>
#include <Cuboid/Renderer/VertexArray.h>
#include <glad/glad.h>
#include <glm/glm.hpp>


namespace Cuboid
{
	void OpenGLMessageCallback(
			unsigned source,
			unsigned type,
			unsigned id,
			unsigned severity,
			int length,
			const char* message,
			const void* userParam)
	{
		switch (severity)
		{
		case GL_DEBUG_SEVERITY_HIGH:         CUBOID_CORE_CRITICAL(message); return;
		case GL_DEBUG_SEVERITY_MEDIUM:       CUBOID_CORE_ERROR(message); return;
		case GL_DEBUG_SEVERITY_LOW:          CUBOID_CORE_WARN(message); return;
		case GL_DEBUG_SEVERITY_NOTIFICATION: CUBOID_CORE_TRACE(message); return;
		}

		CUBOID_CORE_ASSERT(false, "Unknown severity level!");
	}

	void OpenGLRendererAPI::Init()
	{

#if CUBOID_DEBUG
		glEnable(GL_DEBUG_OUTPUT);
		glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
		glDebugMessageCallback(OpenGLMessageCallback, nullptr);
		glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DEBUG_SEVERITY_NOTIFICATION, 0, NULL, GL_FALSE);
#endif

		glEnable(GL_BLEND);
		glBlendEquation(GL_FUNC_ADD);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_CULL_FACE);
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_SCISSOR_TEST);

		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);



	}


	void OpenGLRendererAPI::SetClearColor(const glm::vec4& clearColor)
	{
		glClearColor(clearColor.r, clearColor.g, clearColor.b, clearColor.a);
	}

	void OpenGLRendererAPI::Clear()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}


	void OpenGLRendererAPI::DrawIndexed(const Ref<VertexArray>& vertexArray, uint32_t indexCount, uint32_t mode)
	{
        vertexArray->Bind();
		uint32_t count = indexCount ? indexCount : vertexArray->GetIndexBuffer()->GetCount();
		glDrawElements(mode, count, GL_UNSIGNED_INT, nullptr);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	void OpenGLRendererAPI::SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
	{
		glViewport(x, y, width, height);
	}

	OpenGLRendererAPI::~OpenGLRendererAPI()
	{
	}

	void OpenGLRendererAPI::Draw(const Ref<VertexArray>& vertexArray, uint32_t vertexCount, uint32_t startVertex)
	{
	}

}
