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


		if (ImGui::IsMouseDown(0) && ImGui::IsWindowHovered())
		{
			m_EntitySelection = {  };
		}

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

			if (ImGui::TreeNodeEx((const void*)typeid(TransformComponent).hash_code(), ImGuiTreeNodeFlags_DefaultOpen, "Transform"))
			{
				

				ImGui::DragFloat3("Position", glm::value_ptr(transform[3]), 0.1f);
				ImGui::TreePop();
			}
		}

		if (entity.HasComponent<SpriteRendererComponent>())
		{
			auto& color = entity.GetComponent<SpriteRendererComponent>().Color;

			if (ImGui::TreeNodeEx((const void*)typeid(SpriteRendererComponent).hash_code(), ImGuiTreeNodeFlags_DefaultOpen, "SpriteRenderer"))
			{


				ImGui::ColorEdit4("Color", glm::value_ptr(color));
				ImGui::TreePop();
			}
		}

		if (entity.HasComponent<CameraComponent>())
		{
			

			if (ImGui::TreeNodeEx((const void*)typeid(CameraComponent).hash_code(), ImGuiTreeNodeFlags_DefaultOpen, "Camera"))
			{
				auto& camera = entity.GetComponent<CameraComponent>().Camera;
				auto& cameraComponent = entity.GetComponent<CameraComponent>();

				const char* projectionTypeString[] = { "Persepective", "Orthographic" };
				 const char* currentSelected = projectionTypeString[(int)camera.GetCameraProjectionType()];

				 ImGui::Checkbox("Primary", &cameraComponent.Primary);

				 if (ImGui::BeginCombo("Projection", currentSelected))
				 {


					 for (int i = 0; i < 2; i++)
					 {

						 bool isSelected = currentSelected == projectionTypeString[i];

						 if (ImGui::Selectable(projectionTypeString[i], &isSelected))
						 {

							 currentSelected = projectionTypeString[i];
							 camera.SetCameraProjectionType((SceneCamera::CameraProjectionType)i);
						 }

						 if (isSelected)
						 {
							 ImGui::SetItemDefaultFocus();
						 }
					 }

					 ImGui::EndCombo();

				 }

					if (camera.GetCameraProjectionType() == SceneCamera::CameraProjectionType::Perspective)
					{


						
							float fov = glm::degrees(camera.GetPerspectiveVerticalFOV());

							if (ImGui::DragFloat("FOV", &fov))
								camera.SetPerspectiveVerticalFOV(glm::radians(fov));
					
							float nearClip = camera.GetPerspectiveNearClip();

								if (ImGui::DragFloat("Near", &nearClip))
									camera.SetPerspectiveNearClip(nearClip);

					
							float farClip = camera.GetPerspectiveFarClip();

								if (ImGui::DragFloat("Far", &farClip))
									camera.SetPerspectiveFarClip(farClip);

					}

					else if (camera.GetCameraProjectionType() == SceneCamera::CameraProjectionType::Orthographic)
					{
						
							float orthoSize = camera.GetOrthographicSize();

							if (ImGui::DragFloat("Size", &orthoSize))
								camera.SetOrthographicSize(orthoSize);
					

						
							float nearClip = camera.GetOrthoGraphicNearClip();

							if (ImGui::DragFloat("Near", &nearClip))
								camera.SetOrthoGraphicNearClip(nearClip);

						

						
							float farClip = camera.GetOrthoGraphicFarClip();

							if (ImGui::DragFloat("Far", &farClip))
								camera.SetOrthoGraphicFarClip(farClip);

							ImGui::Checkbox("Fixed Aspect", &cameraComponent.FixedAspectRatio);
						
					}

				ImGui::TreePop();
			}
		}

	}

}