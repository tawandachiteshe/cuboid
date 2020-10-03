#include <d3gpch.h>
#include <D3NGINE/Renderer/Renderer.h>
#include <D3NGINE/Renderer/VertexArray.h>
#include <glm/glm.hpp>
#include "Renderer2D.h"

namespace D3G
{
	Scope<Renderer::SceneData> Renderer::m_SceneData = CreateScope<Renderer::SceneData>();

	void Renderer::BeginScene(const Camera2D& camera)
	{
		m_SceneData->m_ProjectionViewMatrix = camera.GetViewProjectionMatrix();
	}

	void Renderer::EndScene()
	{
	}

	void Renderer::Submit(const Ref<VertexArray> &vtxArray, const Ref<Shader>& shader, const glm::mat4& transform)
	{

		shader->Bind();
		vtxArray->Bind();
		shader->SetMat4("u_Transform", transform);

		shader->SetMat4("u_ProjectionViewMatrix", m_SceneData->m_ProjectionViewMatrix);
		RenderCommand::DrawIndexed(vtxArray);
	}

	void Renderer::OnWindowResize(uint32_t width, uint32_t height)
	{
		RenderCommand::SetViewport(0, 0, width, height);
	}

	void Renderer::ShutDown()
	{
		Renderer2D::ShutDown();
	}

	void Renderer::Init()
	{
		RenderCommand::Init();
		//TODO: Uncomment Renderer2d and make it flexible
		Renderer2D::Init();
	}

}
