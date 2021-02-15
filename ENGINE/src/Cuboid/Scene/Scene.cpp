#include "Cuboidpch.h"
#include "Scene.h"

#include <glm/glm.hpp>
#include "Entity.h"
#include "Cuboid/Renderer/Renderer2D.h"
#include "Cuboid/Renderer/Renderer.h"
#include "Components.h"

namespace Cuboid
{
	Scene::Scene()
	{

	}


	Scene::~Scene()
	{
	}


	void Scene::OnUpdate(float ts)
	{

		{

			m_Registry.view<NativeScriptComponent>().each([=](auto entity, auto& nsc) {

				if (!nsc.Instance)
				{
				
					nsc.Instance = nsc.InstantiateScript();

					nsc.Instance->m_Entity = Entity { entity, this };

					nsc.Instance->OnCreate();
				}

				nsc.Instance->OnUpdate(ts);

				});

		}

		Camera* mainCamera = nullptr;
		glm::mat4 mainCameraTranform;

		{

			auto view = m_Registry.view<TransformComponent, CameraComponent>();

			for (auto entity : view)
			{
				auto [transform, camera] = view.get<TransformComponent, CameraComponent>(entity);

				

				if (camera.Primary)
				{
					mainCamera = &camera.Camera;
					mainCameraTranform = transform.GetTransform();
					
					break;
				}

			}

		}

		if (mainCamera)
		{
			Renderer2D::BeginScene(*mainCamera, mainCameraTranform);
			auto group = m_Registry.group<TransformComponent>(entt::get<SpriteRendererComponent>);

			for (auto entity : group)
			{
				auto [transform, sprite] = group.get<TransformComponent, SpriteRendererComponent>(entity);

				Renderer2D::DrawQuad(transform.GetTransform(), sprite.Color);

			}
			Renderer2D::EndScene();

		}

		if (mainCamera)
		{
#if 0
			Renderer::BeginScene(*mainCamera, mainCameraTranform);
			auto view = m_Registry.view<TransformComponent, MeshRendererComponent>();


			for (auto entity : view)
			{
				auto [transform, mesh] = view.get<TransformComponent, MeshRendererComponent>(entity);
				Renderer::Submit(mesh.mesh.GetVertexArray(), mesh.shader, transform.GetTransform());
				Renderer::EndScene();

			}

#endif

		}

	}

	void Scene::OnViewportResize(uint32_t width, uint32_t height)
	{

		m_ViewportWidth = width;
		m_ViewportHeight = height;

		auto view = m_Registry.view<CameraComponent>();

		for (auto entity : view)
		{

			auto& cameraComponent = view.get<CameraComponent>(entity);

			if (!cameraComponent.FixedAspectRatio)
			{
				cameraComponent.Camera.SetViewportSize(width, height);
			}

		}


	}


	Entity Scene::CreateEntity(const std::string name)
	{
		Entity entity = { m_Registry.create(), this };

		entity.AddComponent<TransformComponent>();

		auto& tag = entity.AddComponent<TagComponent>(name);

		if (tag.Tag.empty())
			tag.Tag = "Empty";
		else
			tag.Tag = name;

		return entity;
	}

	void Scene::DestroyEntity(Entity entity)
	{
		m_Registry.destroy(entity);
	}

	template<typename T>
	void Scene::OnComponentAdded(Entity entity, T& component)
	{
		static_assert(true);
	}

	template<>
	void Scene::OnComponentAdded<TransformComponent>(Entity entity, TransformComponent& component)
	{
	}

	template<>
	void Scene::OnComponentAdded<NativeScriptComponent>(Entity entity, NativeScriptComponent& component)
	{
	}


	template<>
	void Scene::OnComponentAdded<TagComponent>(Entity entity, TagComponent& component)
	{
	}

	template<>
	void Scene::OnComponentAdded<SpriteRendererComponent>(Entity entity, SpriteRendererComponent& component)
	{
	}

	template<>
	void Scene::OnComponentAdded<MeshRendererComponent>(Entity entity, MeshRendererComponent& component)
	{
	}

	template<>
	void Scene::OnComponentAdded<CameraComponent>(Entity entity, CameraComponent& component)
	{
		component.Camera.SetViewportSize(m_ViewportWidth, m_ViewportHeight);
	}

}
