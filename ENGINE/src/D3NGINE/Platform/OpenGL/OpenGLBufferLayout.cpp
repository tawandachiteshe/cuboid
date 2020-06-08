#include <D3NGINE/Platform/OpenGL/OpenGLBufferLayout.h>
#include <glad/glad.h>

namespace D3G
{

	OpenGLBufferLayout::OpenGLBufferLayout() :
		m_Stride(0)
	{

	}


	OpenGLBufferLayout::~OpenGLBufferLayout()
	{
	}



	template<>
	void OpenGLBufferLayout::Push<float>(unsigned int count)
	{
		m_ElementLayouts.push_back({ GL_FLOAT, count, GL_FALSE });
		m_Stride += count * OpenGLVertexBufferElement::GetSizeOfType(GL_FLOAT);
	}

	template<>
	void OpenGLBufferLayout::Push<unsigned int>(unsigned int count)
	{
		m_ElementLayouts.push_back({ GL_UNSIGNED_INT, count, GL_FALSE });
		m_Stride += count * OpenGLVertexBufferElement::GetSizeOfType(GL_UNSIGNED_INT);
	}

	template<>
	void OpenGLBufferLayout::Push<unsigned char>(unsigned int count)
	{
		m_ElementLayouts.push_back({ GL_UNSIGNED_BYTE, count, GL_TRUE });
		m_Stride += count * OpenGLVertexBufferElement::GetSizeOfType(GL_UNSIGNED_BYTE);
	}

	inline uint32_t OpenGLBufferLayout::GetStride() const
	{
		return m_Stride;
	}

	Ref<std::vector<VertexBufferElement>> OpenGLBufferLayout::GetElements() const
	{
		Ref<std::vector<VertexBufferElement>> data = CreateRef<std::vector<VertexBufferElement>>();
		for(OpenGLVertexBufferElement elem : m_ElementLayouts)
		{
			data->insert(data->begin(), elem);
		}
		return data;
	}

}
