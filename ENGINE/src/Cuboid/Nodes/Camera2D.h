#pragma once
#include <glm/glm.hpp>


namespace D3G
{

	class Camera2D
	{

	public:
		Camera2D(float left, float right, float bottom, float top);

		const glm::vec3& GetPosition() const { return m_Position; }
		float GetRotation() const { return m_Rotation; }

		void SetPosition(const glm::vec3& pos) { m_Position = pos; ReCalculateViewMatrix(); }
		void SetRotation(float rotation) { m_Rotation = rotation; ReCalculateViewMatrix(); }
		void SetScale(const glm::vec3& scale) { m_Scale = scale;  ReCalculateViewMatrix();}

		const glm::mat4& GetProjMat() const
		{
			return m_ProjMat;
		}

		const glm::mat4& GetProjViewMat() const
		{
			return m_ProjViewMat;
		}

		const glm::mat4& GeMViewMat() const
		{
			return m_ViewMat;
		}

	private:
		glm::mat4 m_ProjMat;
		glm::mat4 m_ViewMat;
		glm::mat4 m_ProjViewMat;

		float m_Rotation = 0;
		glm::vec3 m_Position = { 0.0f, 0.0f, 0.0f };
		glm::vec3 m_Scale = { 1.0f, 1.0f, 1.0f };
	private:

		void ReCalculateViewMatrix();

	};

}
