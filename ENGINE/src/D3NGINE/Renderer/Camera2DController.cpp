#include <D3NGINE/Renderer/Camera2DController.h>
#include "D3NGINE/Core/Input.h"
#include <D3NGINE/Core/Application.h>


namespace D3G {

	Camera2DController::Camera2DController(float aspectRatio, bool rotation)
	: m_AspectRatio(aspectRatio), m_Camera(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel), m_Rotation(rotation)
	{
	}

	void Camera2DController::OnUpdate(float ts)
	{
		//HZ_PROFILE_FUNCTION();

		if (Input::IsKeyPressed(D3G_KEY_A))
		{
			m_CameraPosition.x -= cos(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * ts;
			m_CameraPosition.y -= sin(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * ts;
		}
		else if (Input::IsKeyPressed(D3G_KEY_D))
		{
			m_CameraPosition.x += cos(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * ts;
			m_CameraPosition.y += sin(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * ts;
		}

		if (Input::IsKeyPressed(D3G_KEY_W))
		{
			m_CameraPosition.x += -sin(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * ts;
			m_CameraPosition.y += cos(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * ts;
		}
		else if (Input::IsKeyPressed(D3G_KEY_S))
		{
			m_CameraPosition.x -= -sin(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * ts;
			m_CameraPosition.y -= cos(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * ts;
		}

		if (m_Rotation)
		{
			if (Input::IsKeyPressed(D3G_KEY_Q))
				m_CameraRotation += m_CameraRotationSpeed * ts;
			if (Input::IsKeyPressed(D3G_KEY_E))
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

		dispatcher.Dispatch<MouseScrolledEvent>(D3G_BIND_EVENT_FN(Camera2DController::OnMouseScrolled));
		dispatcher.Dispatch<WindowResizeEvent>(D3G_BIND_EVENT_FN(Camera2DController::OnWindowResized));
		

	}

	bool Camera2DController::OnMouseScrolled(MouseScrolledEvent& e)
	{
		D3G_CORE_DEBUG((e.GetYOffset()) * 0.1f);

		m_ZoomLevel -= (e.GetYOffset()) * 0.2f;
		m_ZoomLevel = std::max(m_ZoomLevel, 0.2f);
		m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
		return false;
	}

	bool Camera2DController::OnWindowResized(WindowResizeEvent& e)
	{
		//HZ_PROFILE_FUNCTION();
		int w, h = 0;
		
		w = e.GetWidth();
		h = e.GetHeight();

		m_AspectRatio = (float)w / (float)h;
		m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
		return false;
	}

}
