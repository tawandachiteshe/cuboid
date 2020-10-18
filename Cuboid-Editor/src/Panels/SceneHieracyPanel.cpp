#include "SceneHieracyPanel.h"
#include <imgui.h>
#include "Cuboid/Scene/Components.h"
#include <glm/gtc/type_ptr.hpp> 

namespace Cuboid
{

	void OnImGuiRender()
	{
	}

	SceneHieracyPanel::SceneHieracyPanel(const Ref<Scene>& context)
		: m_Context(context)
	{
	}

	void SceneHieracyPanel::SetContext(const Ref<Scene>& context)
	{
		m_Context = context;
	}

	void SceneHieracyPanel::OnImGuiRender()
	{

		ImGui::Begin("Scene Hierarchy");
		

		m_Context->m_Registry.each([&](auto entityID)
			{


			Entity entity(entityID, m_Context.get());
			DrawEntityNode(entity);

			});

		ImGui::End();


		ImGui::Begin("Properties");


		if (m_EntitySelection)
		{
			DrawComponents(m_EntitySelection);
		}

		ImGui::End();




	}

	void SceneHieracyPanel::DrawEntityNode(Entity& entity)
	{
		auto& tag = entity.GetComponent<TagComponent>().Tag;
		
		ImGuiTreeNodeFlags flags = ((m_EntitySelection == entity) ? ImGuiTreeNodeFlags_Selected : 0) | ImGuiTreeNodeFlags_OpenOnArrow;

		bool opened = ImGui::TreeNodeEx((const void*)(uint64_t)(uint32_t)entity, flags, tag.c_str());

		if (ImGui::IsItemClicked())
		{
			m_EntitySelection = entity;
		}

		if (opened)
		{
			ImGui::TreePop();
		}

	}

	void SceneHieracyPanel::DrawComponents(Entity& entity)
	{
		
		if (entity.HasComponent<TagComponent>())
		{
			auto& tag = entity.GetComponent<TagComponent>().Tag;

			char buffer[256];

			memset(buffer, 0, sizeof(buffer));
			strcpy_s(buffer, sizeof(buffer), tag.c_str());


			if (ImGui::InputText("Tag", buffer, sizeof(buffer)))
			{

				tag = std::string(buffer);

			}
			
			

		}

		if (entity.HasComponent<TransformComponent>())
		{

			auto& transform = entity.GetComponent<TransformComponent>().Transform;

			ImGui::DragFloat3("Position", glm::value_ptr(transform[3]), 0.1f);
		}


	}

}