#pragma once

#include <glm/glm.hpp>

namespace Cuboid
{

	class Camera
	{
	public:
		Camera(const glm::mat4& projection) : m_mtProjection(projection) {}

		const glm::mat4 GetProjection() const {
			return m_mtProjection;
		}

	private:
		glm::mat4 m_mtProjection;

	};


}