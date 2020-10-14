#include "Cuboidpch.h"
#include "Scene.h"

#include <glm/glm.hpp>
#include "Entity.h"
#include "Cuboid/Renderer/Renderer2D.h"

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

		Camera* mainCamera = nullptr;
		glm::mat4* mainCameraTranform = nullptr;

		{

			auto group = m_Registry.view<TransformComponent, CameraComponent>();

			for (auto entity : group)
			{
				auto& [transform, camera] = group.get<TransformComponent, CameraComponent>(entity);

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

		auto group = m_Registry.view<TransformComponent, SpriteRendererComponent>();

		for (auto entity : group)
		{
			auto& [transform, sprite] = group.get<TransformComponent, SpriteRendererComponent>(entity);

			Renderer2D::DrawQuad(transform, sprite.Color);

		}

		Renderer2D::EndScene();

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
