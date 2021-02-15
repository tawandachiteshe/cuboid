#include "OpenGLIndexBuffer.h"
#include <glad/glad.h>

namespace Cuboid
{

	OpenGLIndexBuffer::OpenGLIndexBuffer(uint32_t* indices, uint32_t size) :
		m_Count(size)
	{
		glGenBuffers(1, &m_RendererID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_Count * sizeof(unsigned int), indices , GL_STATIC_DRAW);

	}

	uint32_t OpenGLIndexBuffer::GetCount() const { return m_Count; }

	void OpenGLIndexBuffer::Bind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
	}

	void OpenGLIndexBuffer::UnBind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}


	OpenGLIndexBuffer::~OpenGLIndexBuffer()
	{
		glDeleteBuffers(1, &m_RendererID);
	}
}
