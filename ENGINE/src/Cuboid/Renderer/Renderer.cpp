#include <Cuboidpch.h>
#include <Cuboid/Renderer/Renderer.h>
#include <Cuboid/Renderer/VertexArray.h>
#include <glm/glm.hpp>
#include "Renderer2D.h"

namespace Cuboid
{
	Scope<Renderer::SceneData> Renderer::m_SceneData = CreateScope<Renderer::SceneData>();

	void Renderer::BeginScene(const Camera2D& camera)
	{
		m_SceneData->m_ProjectionViewMatrix = camera.GetViewProjectionMatrix();
	}

	void Renderer::BeginScene(const Camera& camera, const glm::mat4& transform)
	{
		m_SceneData->m_ProjectionViewMatrix = camera.GetProjection() * glm::inverse(transform);
	}

	void Renderer::EndScene()
	{
	}

	struct MVP
	{
		glm::mat4 transform;
		glm::mat4 projectionview;
		glm::mat4 inverseTranposeTransform;

	};

	void Renderer::Submit(const Ref<VertexArray> &vtxArray, const Ref<Shader>& shader, const glm::mat4& transform)
	{

		shader->Bind();
		vtxArray->Bind();

		if (RendererAPI::GetAPI() == RendererAPI::API::Opengl)
		{
			shader->SetMat4("u_ProjectionViewMatrix", m_SceneData->m_ProjectionViewMatrix);
			shader->SetMat4("u_Transform", transform);
		}
		else if (RendererAPI::GetAPI() == RendererAPI::API::DirectX)
		{

			shader->GetConstantBuffer()->SetConstantBufferData<MVP>("MVP", [&](MVP* mvp)
				{
					glm::mat in = glm::mat4(1.0f);
					mvp->transform = transform;
					mvp->projectionview = m_SceneData->m_ProjectionViewMatrix;
					mvp->inverseTranposeTransform = glm::inverse(glm::transpose(transform));

				});

		}
		
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
