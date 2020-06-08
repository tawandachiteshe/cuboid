#include <D3NGINE/Platform/OpenGL/common.h>
#include <D3NGINE/Platform/OpenGL/OpenGLIndexBuffer.h>
#include <glad\glad.h>
namespace D3G
{

	OpenGLIndexBuffer::OpenGLIndexBuffer(uint32_t* indices, uint32_t size) :
		m_Count(size)
	{
		ThrowIfError(glGenBuffers(1, &m_RendererID));
		ThrowIfError(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID));
		ThrowIfError(glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_Count * sizeof(unsigned int), indices , GL_STATIC_DRAW));

	}

	uint32_t OpenGLIndexBuffer::GetCount() const { return m_Count; }

	void OpenGLIndexBuffer::Bind() const
	{
		ThrowIfError(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID));
	}

	void OpenGLIndexBuffer::UnBind() const
	{
		ThrowIfError(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
	}


	OpenGLIndexBuffer::~OpenGLIndexBuffer()
	{
		ThrowIfError(glDeleteBuffers(1, &m_RendererID));
	}
}
