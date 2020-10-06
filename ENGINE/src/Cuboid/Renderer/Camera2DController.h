

#include "Cuboid/Renderer/Camera2D.h"
#include <glm/glm.hpp>

#include "Cuboid/Events/Event.h"
#include "Cuboid/Events/ApplicationEvent.h"
#include "Cuboid/Events/MouseEvent.h"

#ifndef CUBOID_RENDERER_CAMERA2D_CTRLER_H
#define CUBOID_RENDERER_CAMERA2D_CTRLER_H

namespace Cuboid {



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

		void OnResize(float width, float height);
	private:

		bool OnMouseScrolled(MouseScrolledEvent& e);
		bool OnWindowResized(WindowResizeEvent& e);
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
