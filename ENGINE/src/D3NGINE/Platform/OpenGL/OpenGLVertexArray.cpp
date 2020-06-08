#include <glad/glad.h>
#include <D3NGINE/Platform/OpenGL/OpenGLVertexArray.h>
#include <D3NGINE/Platform/OpenGL/OpenGLShader.h>
#include <d3gpch.h>

namespace D3G
{


	OpenGLVertexArray::OpenGLVertexArray()
	{
		ThrowIfError(glGenVertexArrays(1, &m_RendererID));

	}

	void OpenGLVertexArray::Bind() const
	{
		ThrowIfError(glBindVertexArray(m_RendererID));
	}

	void OpenGLVertexArray::UnBind() const
	{
		ThrowIfError(glBindVertexArray(0));
	}

	OpenGLVertexArray::~OpenGLVertexArray()
	{
		ThrowIfError(glDeleteVertexArrays(1, &m_RendererID));
	}

	const Ref<IndexBuffer>& OpenGLVertexArray::GetIndexBuffer() const
	{
		return m_IdxBuffer;
	}



	void OpenGLVertexArray::AddVertexBuffer(
			const Ref<VertexBuffer> &vtxBuffer) const
	{
		Bind();
		vtxBuffer->Bind();
		const auto& elements = vtxBuffer->GetBufferLayout()->GetElements();
		const auto& elementsData = vtxBuffer->GetBufferLayoutData();
		unsigned int offset = 0;
		int attrib = 0;
		for (int i = 0; i < elements->size(); i++)
		{


			const auto& element = (*elements)[i];
			const auto& key = (*elementsData)[i];
			std::string _key;
			attrib = std::dynamic_pointer_cast<OpenGLShader>(m_Shader)->GetAttributeLocation(key.second);

			ThrowIfError(glEnableVertexAttribArray(attrib));
			ThrowIfError(glVertexAttribPointer(attrib, element.count, element.type, element.normalized,
					vtxBuffer->GetBufferLayout()->GetStride(), ((const void*)offset)));
			offset += element.count * OpenGLVertexBufferElement::GetSizeOfType(element.type);

			D3G_CORE_INFO("attrib location {0} attrib name {1} ",attrib, key.second);
		}
	}

	void OpenGLVertexArray::SetIndexBuffer(
			const Ref<IndexBuffer>& idxBuffer)
	{
		m_IdxBuffer = idxBuffer;
		m_IdxBuffer->Bind();
	}

	void OpenGLVertexArray::SetShader(const Ref<Shader> &mShader)
	{
		m_Shader = mShader;
	}

}
