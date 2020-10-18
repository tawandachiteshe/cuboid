#include "Cuboidpch.h"
#include "Scene.h"

#include <glm/glm.hpp>
#include "Entity.h"
#include "Cuboid/Renderer/Renderer2D.h"
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
		glm::mat4* mainCameraTranform = nullptr;

		{

			auto view = m_Registry.view<TransformComponent, CameraComponent>();

			for (auto entity : view)
			{
				auto [transform, camera] = view.get<TransformComponent, CameraComponent>(entity);

				

				if (camera.Primary)
				{
					mainCamera = &camera.Camera;
					mainCameraTranform = &transform.Transform;
					
					break;
				}

			}

		}

		if (mainCamera)
		{
			Renderer2D::BeginScene(*mainCamera, *mainCameraTranform);
		}

		auto group = m_Registry.group<TransformComponent>(entt::get<SpriteRendererComponent>);

		for (auto entity : group)
		{
			auto [transform, sprite] = group.get<TransformComponent, SpriteRendererComponent>(entity);

			Renderer2D::DrawQuad(transform, sprite.Color);

		}

		Renderer2D::EndScene();

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
}
