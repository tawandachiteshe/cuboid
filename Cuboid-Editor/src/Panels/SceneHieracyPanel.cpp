#include "SceneHieracyPanel.h"
#include <imgui.h>
#include <imgui_internal.h>
#include "Cuboid/Scene/Components.h"
#include <glm/gtc/type_ptr.hpp> 

namespace Cuboid
{

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

		if (ImGui::BeginPopupContextWindow(0, 1, false))
		{
			if (ImGui::MenuItem("Create Empty Entity"))
				m_Context->CreateEntity("Empty Entity");

			ImGui::EndPopup();
		}

		ImGui::End();


		ImGui::Begin("Properties");

		auto contentRegAvail = ImGui::GetContentRegionAvail();

		if (m_EntitySelection)
		{
			DrawComponents(m_EntitySelection);

			ImGui::PushItemWidth(-1.0f);
			ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2{ 0, 0 });
			if (ImGui::Button("Add Component", { contentRegAvail.x , 25.0f }))
				ImGui::OpenPopup("AddComponent");

			ImGui::PopStyleVar();

			if (ImGui::BeginPopup("AddComponent"))
			{

				if (ImGui::MenuItem("Camera"))
				{

					m_EntitySelection.AddComponent<CameraComponent>();
					ImGui::CloseCurrentPopup();
				}

				if (ImGui::MenuItem("Sprite Renderer"))
				{

					m_EntitySelection.AddComponent<SpriteRendererComponent>();
					ImGui::CloseCurrentPopup();
				}


				ImGui::EndPopup();

			}

		}

		ImGui::End();




	}

	void SceneHieracyPanel::DrawEntityNode(Entity& entity)
	{
		auto& tag = entity.GetComponent<TagComponent>().Tag;

		ImGuiTreeNodeFlags flags = ((m_EntitySelection == entity) ? ImGuiTreeNodeFlags_Selected : 0) | ImGuiTreeNodeFlags_OpenOnArrow;
		flags |= ImGuiTreeNodeFlags_SpanAvailWidth;

		bool opened = ImGui::TreeNodeEx((const void*)(uint64_t)(uint32_t)entity, flags, tag.c_str());

		if (ImGui::IsItemClicked())
		{
			m_EntitySelection = entity;
		}

		bool isTheEntityDeleted = false;

		if (ImGui::BeginPopupContextItem())
		{
			if (ImGui::MenuItem("Delete Entity"))
				isTheEntityDeleted = true;

			ImGui::EndPopup();
		}

		if (opened)
		{
			ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_SpanAvailWidth;

			bool opened = ImGui::TreeNodeEx((const void*)781212, flags, tag.c_str());

			if (opened)
				ImGui::TreePop();

			ImGui::TreePop();
		}


		if (isTheEntityDeleted)
		{
			if (m_EntitySelection == entity)
			{
				m_EntitySelection = { };
			}
			m_Context->DestroyEntity(entity);
		}
			

	}

	static void DrawVec3UI(const char* label, glm::vec3& values, float resetValue = 0.0f, float columnWidth = 100.0f)
	{
		ImGuiIO& io = ImGui::GetIO();
		auto boldFont = io.Fonts->Fonts[0];

		ImGui::PushID(label);

		ImGui::Columns(2);
		ImGui::SetColumnWidth(0,columnWidth);
		ImGui::Text(label);
		ImGui::NextColumn();

		ImGui::PushMultiItemsWidths(3, ImGui::CalcItemWidth());
		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{ 0, 0 });

		float lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;
		ImVec2 buttonSize = { lineHeight + 3.0f, lineHeight };

		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4 {0.8f, 0.1f, 0.12f, 1.0f});
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.9f, 0.15f, 0.12f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.8f, 0.1f, 0.12f, 1.0f });

		ImGui::PushFont(boldFont);
		if (ImGui::Button("X", buttonSize))
			values.x = resetValue;
		ImGui::PopFont();

		ImGui::PopStyleColor(3);

		ImGui::SameLine();
		ImGui::DragFloat("##X", &values.x, 0.1f, 0.0f, 0.0f, "%.2f");
		ImGui::PopItemWidth();
		ImGui::SameLine();

		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.15f, 0.8f, 0.15f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.15f, 0.9f, 0.15f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.15f, 0.8f, 0.15f, 1.0f });

		ImGui::PushFont(boldFont);
		if (ImGui::Button("Y", buttonSize))
			values.y = resetValue;
		ImGui::PopFont();

		ImGui::PopStyleColor(3);

		ImGui::SameLine();
		ImGui::DragFloat("##Y", &values.y, 0.1f, 0.0f, 0.0f, "%.2f");
		ImGui::PopItemWidth();
		ImGui::SameLine();

		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.15f, 0.15f, 0.8f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.15f, 0.15f, 0.9f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.15f, 0.15f, 0.8f, 1.0f });

		ImGui::PushFont(boldFont);
		if (ImGui::Button("Z", buttonSize))
			values.z = resetValue;
		ImGui::PopFont();

		ImGui::PopStyleColor(3);

		ImGui::SameLine();
		ImGui::DragFloat("##Z", &values.z, 0.1f, 0.0f, 0.0f, "%.2f");
		ImGui::PopItemWidth();


		ImGui::PopStyleVar();

		ImGui::Columns(1);

		ImGui::PopID();

	}

	void SceneHieracyPanel::DrawComponents(Entity& entity)
	{
		
		DrawComponentUI<TagComponent>("Tag", entity, [&](auto& component)
		{

				auto& tag = component.Tag;
				char buffer[256];

				memset(buffer, 0, sizeof(buffer));
				strcpy_s(buffer, sizeof(buffer), tag.c_str());

				if (ImGui::InputText("##Tag", buffer, sizeof(buffer)))
				{
					tag = std::string(buffer);
				}

		});


		DrawComponentUI<TransformComponent>("Transform", entity,[&](auto& component)
		{
			auto& transform = component;


			DrawVec3UI("Position", transform.Translation);
			glm::vec3 rotation = glm::degrees(transform.Rotation);
			DrawVec3UI("Rotation", rotation);
			transform.Rotation = glm::radians(rotation);
			DrawVec3UI("Scale", transform.Scale, 1.0f);
			
	
		});

		DrawComponentUI<SpriteRendererComponent>("Sprite Renderer", entity,[](auto& component)
		{
				ImGui::ColorEdit4("Color", glm::value_ptr(component.Color));

		});

		DrawComponentUI<CameraComponent>("Camera", entity, [](auto& component)
		{

				auto& camera = component.Camera;
				auto& cameraComponent = component;

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

		});



	}

	template<typename T, typename UIFunction>
	inline void SceneHieracyPanel::DrawComponentUI(const std::string& componentName, Entity entity, const UIFunction& DrawImGuiFunc)
	{
		const ImGuiTreeNodeFlags treeFlags = ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_Framed | ImGuiTreeNodeFlags_SpanAvailWidth | ImGuiTreeNodeFlags_AllowItemOverlap | ImGuiTreeNodeFlags_FramePadding;

		if (entity.HasComponent<T>())
		{
			auto& component = entity.GetComponent<T>();
			bool removeComponent = false;

			auto contentRegAvail = ImGui::GetContentRegionAvail();

			ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2{ 4, 4 });
			float lineHeight = GImGui->FontSize + GImGui->Style.FramePadding.y * 2.0f;
			ImGui::Separator();

			bool open = ImGui::TreeNodeEx((const void*)typeid(T).hash_code(), treeFlags, componentName.c_str());
			ImGui::PopStyleVar();


			ImGui::SameLine(contentRegAvail.x - lineHeight * .5f);
			if (ImGui::Button("+", ImVec2{ lineHeight, lineHeight }))
			{
				ImGui::OpenPopup("ComponentSettings");
			}


			if (ImGui::BeginPopup("ComponentSettings"))
			{

				if (ImGui::MenuItem("Remove Component"))
					removeComponent = true;


				ImGui::EndPopup();
			}

			if (open)
			{

				DrawImGuiFunc(component);
				ImGui::TreePop();
			}

			if (removeComponent)
			{
				entity.RemoveComponent<T>();
			}
		}

	}

}