#include "d3gpch.h"
#include <D3NGINE/Nodes/Camera2D.h>

#include <glm/gtc/matrix_transform.hpp>

namespace D3G
{


	Camera2D::Camera2D(float left, float right, float bottom, float top):
		m_ProjMat(glm::ortho(left, right, bottom, top, -1.0f, 1.0f )), m_ViewMat(1.0f)
	{
		m_ProjViewMat = m_ProjMat * m_ViewMat;
	}

	void Camera2D::ReCalculateViewMatrix()
	{
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_Position) *
				glm::rotate(glm::mat4(1.0f), glm::radians(m_Rotation), glm::vec3(0.0f, 0.0f, 1.0f)) *
				glm::scale(glm::mat4(1.0f), m_Scale);

		m_ViewMat = glm::inverse(transform);

		m_ProjViewMat = m_ProjMat * m_ViewMat;
	}

}
