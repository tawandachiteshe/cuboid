#pragma once

#include "Cuboid/Renderer/Camera.h"

namespace Cuboid
{

	class SceneCamera : public Camera
	{

	public:

	    enum class CameraProjectionType
		{
			Perspective = 0, Orthographic = 1
		};

	public:

		SceneCamera();

		virtual ~SceneCamera() =  default;

		void SetOrthoGraphic(float size, float nearClip, float farClip);
		void SetPerspective(float verticalFOV, float nearClip, float farClip);

		void SetViewportSize(uint32_t width, uint32_t height);

		float	GetPerspectiveVerticalFOV() const { return m_PerspectiveFOV; }
		void	SetPerspectiveVerticalFOV(float size) { m_PerspectiveFOV = size; RecalculateProjection(); }
		float	GetPerspectiveNearClip() const { return m_PerspectiveNear; }
		float	GetPerspectiveFarClip() const { return m_PerspectiveFar; }
		void	SetPerspectiveNearClip(float value) { m_PerspectiveNear = value; RecalculateProjection(); }
		void	SetPerspectiveFarClip(float value) { m_PerspectiveFar = value; RecalculateProjection(); }

		float	GetOrthographicSize() const { return m_OrthographicSize; }
		void	SetOrthographicSize(float size) { m_OrthographicSize = size; RecalculateProjection(); }
		float	GetOrthoGraphicNearClip() const { return m_OrthographicNear; }
		float	GetOrthoGraphicFarClip() const { return m_OrthographicFar; }
		void	SetOrthoGraphicNearClip(float value) {  m_PerspectiveFar = value; RecalculateProjection(); }
		void	SetOrthoGraphicFarClip(float value) {  m_OrthographicFar = value; RecalculateProjection(); }

		CameraProjectionType GetCameraProjectionType() const { return m_ProjectionType; }
		void SetCameraProjectionType(CameraProjectionType type) { m_ProjectionType = type; RecalculateProjection(); }

	private:

		void RecalculateProjection();

	private:

		float m_OrthographicSize = 10.0f;
		float m_OrthographicNear = -1.0f;
		float m_OrthographicFar = 1.0f;

		float m_PerspectiveFOV = glm::radians(45.0f);
		float m_PerspectiveNear = 0.01f;
		float m_PerspectiveFar = 1000.0f;

		float m_AspectRatio = 0.0f;
		CameraProjectionType m_ProjectionType = CameraProjectionType::Orthographic;

	};

}