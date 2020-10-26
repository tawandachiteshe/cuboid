#pragma once

#include "entt/entt.hpp"


namespace Cuboid
{
	class Entity;
	class SceneHieracyPanel;
	class SceneSerializer;

	class Scene
	{
	public:
		Scene();
		~Scene();

		void OnUpdate(float ts);

		void OnViewportResize(uint32_t width, uint32_t height);

		Entity CreateEntity(const std::string name = "");
		void DestroyEntity(Entity entity);

	private:

		template<typename T>
		void OnComponentAdded(Entity entity, T& component);

	private:
		entt::registry m_Registry;

		friend class Entity;
		friend class SceneSerializer;
		friend class SceneHieracyPanel;
		

		uint32_t m_ViewportWidth = 0u;
		uint32_t m_ViewportHeight = 0u;
	};

}