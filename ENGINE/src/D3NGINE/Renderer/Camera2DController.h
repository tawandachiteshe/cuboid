

#include "D3NGINE/Renderer/Camera2D.h"
#include <SDL_events.h>
#include <glm/glm.hpp>

#include "D3NGINE/Events/Event.h"

#ifndef D3G_RENDERER_CAMERA2D_CTRLER_H
#define D3G_RENDERER_CAMERA2D_CTRLER_H

namespace D3G {



	class Camera2DController
	{
	public:
			Camera2DController(float aspectRatio, bool rotation = false);

		void OnUpdate(float ts);
		void OnEvent(Event& e);

		Camera2D& GetCamera() { return m_Camera; }
		const Camera2D& GetCamera() const { return m_Camera; }

		float GetZoomLevel() const { return m_ZoomLevel; }
		void SetZoomLevel(float level) { m_ZoomLevel = level; }
	private:

		bool OnMouseScrolled(SDL_MouseWheelEvent& e);
		bool OnWindowResized(SDL_WindowEvent& e);
	private:
		float m_AspectRatio;
		float m_ZoomLevel = 1.0f;
		Camera2D m_Camera;
		bool m_Rotation;

		glm::vec3 m_CameraPosition = { 0.0f, 0.0f, 0.0f };
		float m_CameraRotation = 0.0f; //In degrees, in the anti-clockwise direction
		float m_CameraTranslationSpeed = 15.0f, m_CameraRotationSpeed = 180.0f;
	};

}

#endif
