#pragma once

#include <glm/glm.hpp>

struct DirectionalLight
{

	glm::vec3 m_Direction;
	glm::vec3 m_Color;
	float m_Intensity;

	glm::vec3 GetDirection()
	{
		return glm::normalize(m_Direction * -1.0f);
	}

	glm::vec3 GetLightColor()
	{
		return m_Color * m_Intensity;
	}

};