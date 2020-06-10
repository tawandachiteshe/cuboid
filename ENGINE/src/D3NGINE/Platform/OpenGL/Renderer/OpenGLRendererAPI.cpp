#include <D3NGINE/Platform/OpenGL/Renderer/OpenGLRendererAPI.h>
#include <D3NGINE/Renderer/VertexArray.h>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <d3gpch.h>

#include "imgui_impl_opengl3.h"

namespace D3G
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
		case GL_DEBUG_SEVERITY_HIGH:         D3G_CORE_CRITICAL(message); return;
		case GL_DEBUG_SEVERITY_MEDIUM:       D3G_CORE_ERROR(message); return;
		case GL_DEBUG_SEVERITY_LOW:          D3G_CORE_WARN(message); return;
		case GL_DEBUG_SEVERITY_NOTIFICATION: D3G_CORE_TRACE(message); return;
		}

		D3G_CORE_ASSERT(false, "Unknown severity level!");
	}

	void OpenGLRendererAPI::Init()
	{

#ifdef D3G_BUILD_DEBUG
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

}