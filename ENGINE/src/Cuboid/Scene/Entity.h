#pragma once

#include <entt\entt.hpp>
#include "Scene.h"
#include <limits.h>

namespace Cuboid
{
	class Entity
	{
	public:
		Entity() = default;
		Entity(entt::entity handle, Scene* scene);
		Entity(const Entity& other) = default;

		template<typename T, typename... Args>
		T& AddComponent(Args&&... args)
		{
			CUBOID_ASSERT(!HasComponent<T>(), "Already has component");
			return m_pScene->m_Registry.emplace<T>(m_entEntityHandle, std::forward<Args>(args)...);
		}

		template<typename T>
		T& GetComponent()
		{
			CUBOID_ASSERT(HasComponent<T>(), "Component does not exist");
			return m_pScene->m_Registry.get<T>(m_entEntityHandle);
		}

		template<typename T>
		bool HasComponent()
		{
			return m_pScene->m_Registry.has<T>(m_entEntityHandle);
		}

		template<typename T>
		void RemoveComponent()
		{
			CUBOID_ASSERT(HasComponent<T>(), "Component does not exist");
			m_pScene->m_Registry.remove<T>(m_entEntityHandle);
		}

		operator bool() const
		{
			return m_entEntityHandle != entt::null;
		}


	private:

		

		entt::entity m_entEntityHandle{ entt::null };
		Scene* m_pScene = nullptr;

	};
}

