#pragma once

#include "entt/entt.hpp"
#include "Components.h"

namespace Cuboid
{
	class Entity;

	class Scene
	{
	public:
		Scene();
		~Scene();

		void OnUpdate(float ts);

		Entity CreateEntity(const std::string name = "");

	private:
		entt::registry m_Registry;

		friend class Entity;
	};

}