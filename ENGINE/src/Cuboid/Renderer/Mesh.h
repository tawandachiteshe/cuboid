#pragma once


#include <glm/glm.hpp>
#include <vector>
#include <string>

#include "VertexArray.h"
#include "Buffer.h"
#include "Shader.h"


namespace Cuboid
{
	struct VERTEX
	{
		glm::vec3 positions;
		glm::vec2 texcoords;
		//glm::vec4 colors;
		glm::vec3 normals;

	};

	class Mesh
	{
	private:

		std::vector<VERTEX> m_Vertices;
		std::vector<uint32_t> m_Indices;

		Ref<VertexBuffer> m_VertexBuffer;
		Ref<IndexBuffer> m_IndexBuffer;
		Ref<VertexArray> m_VertexArray;

		std::vector<VERTEX>& GetVertices() { return m_Vertices; }
		std::vector<uint32_t>& GetIndices() { return m_Indices; }

	public:

		void AddVertex(const glm::vec3& vertex);

		void SetVertexArray(const Ref<VertexArray>& vertexArray) { m_VertexArray = vertexArray; }

		//TODO make the rendering pipeline better
		Ref<VertexArray>& GetVertexArray() { return m_VertexArray; }

		Ref<VertexBuffer>& GetVertexBuffer() { return m_VertexBuffer; }

		Ref<IndexBuffer>& GetIndexBuffer() { return m_IndexBuffer; }

		Mesh() = default;

		Mesh(const std::vector<VERTEX>& vertices, const std::vector<uint32_t>& indices);

	};

}

