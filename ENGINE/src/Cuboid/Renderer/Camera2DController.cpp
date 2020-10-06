#include <Cuboid/Renderer/Camera2DController.h>
#include "Cuboid/Core/Input.h"
#include <Cuboid/Core/Application.h>


namespace Cuboid {

	Camera2DController::Camera2DController(float aspectRatio, bool rotation)
	: m_AspectRatio(aspectRatio), m_Camera(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel), m_Rotation(rotation)
	{
	}

	void Camera2DController::OnUpdate(float ts)
	{
		//HZ_PROFILE_FUNCTION();

		if (Input::IsKeyPressed(CUBOID_KEY_A))
		{
			m_CameraPosition.x -= cos(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * ts;
			m_CameraPosition.y -= sin(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * ts;
		}
		else if (Input::IsKeyPressed(CUBOID_KEY_D))
		{
			m_CameraPosition.x += cos(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * ts;
			m_CameraPosition.y += sin(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * ts;
		}

		if (Input::IsKeyPressed(CUBOID_KEY_W))
		{
			m_CameraPosition.x += -sin(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * ts;
			m_CameraPosition.y += cos(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * ts;
		}
		else if (Input::IsKeyPressed(CUBOID_KEY_S))
		{
			m_CameraPosition.x -= -sin(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * ts;
			m_CameraPosition.y -= cos(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * ts;
		}

		if (m_Rotation)
		{
			if (Input::IsKeyPressed(CUBOID_KEY_Q))
				m_CameraRotation += m_CameraRotationSpeed * ts;
			if (Input::IsKeyPressed(CUBOID_KEY_E))
				m_CameraRotation -= m_CameraRotationSpeed * ts;

			if (m_CameraRotation > 180.0f)
				m_CameraRotation -= 360.0f;
			else if (m_CameraRotation <= -180.0f)
				m_CameraRotation += 360.0f;

			m_Camera.SetRotation(m_CameraRotation);
		}

		m_Camera.SetPosition(m_CameraPosition);

		m_CameraTranslationSpeed = m_ZoomLevel;
	}

	void Camera2DController::OnEvent(Event& e)
	{
		//OnMouseScrolled(e.wheel);

		EventDispatcher dispatcher(e);

		dispatcher.Dispatch<MouseScrolledEvent>(CUBOID_BIND_EVENT_FN(Camera2DController::OnMouseScrolled));
		dispatcher.Dispatch<WindowResizeEvent>(CUBOID_BIND_EVENT_FN(Camera2DController::OnWindowResized));
		

	}

	void Camera2DController::OnResize(float width, float height)
	{
		m_AspectRatio = width / height;
		m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
	}

	bool Camera2DController::OnMouseScrolled(MouseScrolledEvent& e)
	{
		CUBOID_CORE_DEBUG((e.GetYOffset()) * 0.1f);

		m_ZoomLevel -= (e.GetYOffset()) * 0.2f;
		m_ZoomLevel = std::max(m_ZoomLevel, 0.2f);
		m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
		return false;
	}

	bool Camera2DController::OnWindowResized(WindowResizeEvent& e)
	{

		OnResize((float)e.GetWidth(), (float)e.GetHeight());
		return false;
	}

}
