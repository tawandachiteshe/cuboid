#include "Mesh.h"

namespace Cuboid
{
    Mesh::Mesh(const std::vector<VERTEX>& vertices, const std::vector<uint32_t>& indices)
    {

        this->m_Vertices = vertices;
        this->m_Indices = indices;

        m_IndexBuffer = IndexBuffer::Create(&m_Indices[0], m_Indices.size());
        m_VertexBuffer = VertexBuffer::Create(&m_Vertices[0], sizeof(VERTEX) * m_Vertices.size());
    }
}