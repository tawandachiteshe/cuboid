#include <d3gpch.h>
#include <D3NGINE/Platform/OpenGL/common.h>
#include <glad/glad.h>
#include <D3NGINE/Platform/OpenGL/OpenGLVertexBuffer.h>

namespace D3G
{

	OpenGLVertexBuffer::OpenGLVertexBuffer(float* vertices, uint32_t size):
									m_Layout(CreateRef<OpenGLBufferLayout>())
	{

		this->m_LayOutData = std::make_shared<ShaderMap>();
		ThrowIfError(glGenBuffers(1, &m_RendererID));
		ThrowIfError(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID));
		ThrowIfError(glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW));

	}


	void OpenGLVertexBuffer::Bind() const
	{
		ThrowIfError(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID));
	}


	void OpenGLVertexBuffer::UnBind() const
	{
		ThrowIfError(glBindBuffer(GL_ARRAY_BUFFER, 0));
	}

	OpenGLVertexBuffer::OpenGLVertexBuffer(uint32_t size):
		m_Layout(CreateRef<OpenGLBufferLayout>())
	{
		this->m_LayOutData = std::make_shared<ShaderMap>();
		ThrowIfError(glGenBuffers(1, &m_RendererID));
		ThrowIfError(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID));
		ThrowIfError(glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_DYNAMIC_DRAW));
	}

	OpenGLVertexBuffer::~OpenGLVertexBuffer()
	{
		ThrowIfError(glDeleteBuffers(1, &m_RendererID));
	}

	void OpenGLVertexBuffer::SetLayOut(const std::vector<VertexLayout>& layout)
	{

		for(int i = 0; i < layout.size(); i++)
		{
			m_LayOutData->push_back({layout[i].dataSize, layout[i].attributeName});
		}

		for(int i = layout.size() - 1; i >= 0; i--)
		{
			m_Layout->Push<float>((uint32_t)layout[i].dataSize);
		}

	}

	const Ref<BufferLayout> OpenGLVertexBuffer::GetBufferLayout() const
	{
		return m_Layout;
	}

	const Ref<ShaderMap>& OpenGLVertexBuffer::GetBufferLayoutData() const
	{
		return m_LayOutData;
	}

    void OpenGLVertexBuffer::SetData(const void *data, uint32_t size)
    {
		glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
		glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
    }


}
