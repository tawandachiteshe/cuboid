#pragma once

#include "Cuboid/Scene/Scene.h"
#include "Cuboid/Core/Core.h"
#include "Cuboid/Scene/Entity.h"


namespace Cuboid
{
	class SceneHieracyPanel
	{

	public:
		SceneHieracyPanel() = default;
		SceneHieracyPanel(const Ref<Scene>& context);

		void SetContext(const Ref<Scene>& context);

		void OnImGuiRender();

	private:

		void DrawEntityNode( Entity& entity);

		void DrawComponents(Entity& entity);

		template<typename T, typename UIFunction>
		void DrawComponentUI(const std::string& componentName, Entity entity,const UIFunction& DrawImGuiFunc);

	private:

		Ref<Scene> m_Context;

		Entity m_EntitySelection;

	};

}

