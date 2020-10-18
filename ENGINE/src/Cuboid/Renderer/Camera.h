#pragma once

#include <glm/glm.hpp>

namespace Cuboid
{

	class Camera
	{
	public:
		Camera() = default;

		Camera(const glm::mat4& projection) : m_mtProjection(projection) {}

		const glm::mat4 GetProjection() const {
			return m_mtProjection;
		}

		virtual ~Camera() = default;

	protected:
		glm::mat4 m_mtProjection = glm::mat4(1.0f);

	};


}