#include <D3NGINE/Renderer/Camera2DController.h>
#include "D3NGINE/Input/D3GINPUT.h"
#include <D3NGINE/Core/Application.h>

extern DECLSPEC void SDLCALL SDL_GetWindowSize(SDL_Window * window, int *w,
				int *h);

namespace D3G {

	Camera2DController::Camera2DController(float aspectRatio, bool rotation)
	: m_AspectRatio(aspectRatio), m_Camera(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel), m_Rotation(rotation)
	{
	}

	void Camera2DController::OnUpdate(float ts)
	{
		//HZ_PROFILE_FUNCTION();

		if (Input::IsKeyDown(SDLK_a))
		{
			m_CameraPosition.x -= cos(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * ts;
			m_CameraPosition.y -= sin(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * ts;
		}
		else if (Input::IsKeyDown(SDLK_d))
		{
			m_CameraPosition.x += cos(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * ts;
			m_CameraPosition.y += sin(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * ts;
		}

		if (Input::IsKeyDown(SDLK_w))
		{
			m_CameraPosition.x += -sin(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * ts;
			m_CameraPosition.y += cos(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * ts;
		}
		else if (Input::IsKeyDown(SDLK_s))
		{
			m_CameraPosition.x -= -sin(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * ts;
			m_CameraPosition.y -= cos(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * ts;
		}

		if (m_Rotation)
		{
			if (Input::IsKeyPressed(SDLK_q))
				m_CameraRotation += m_CameraRotationSpeed * ts;
			if (Input::IsKeyPressed(SDLK_e))
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

	void Camera2DController::OnEvent(SDL_Event* e)
	{
		//OnMouseScrolled(e.wheel);
		OnWindowResized(e->window);

	}

	bool Camera2DController::OnMouseScrolled(SDL_MouseWheelEvent& e)
	{

		//TODO Rebuitl all this crap
		m_ZoomLevel -= (float)(e.y) * 0.25f;
		m_ZoomLevel = std::max(m_ZoomLevel, 0.25f);
		m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
		return false;
	}

	bool Camera2DController::OnWindowResized(SDL_WindowEvent& e)
	{
		//HZ_PROFILE_FUNCTION();
		int w, h = 0;
		SDL_GetWindowSize(Application::Get().ApplicationGetWindow().GetWindow(), &w, &h);
		m_AspectRatio = (float)w / (float)h;
		m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
		return false;
	}

}
