#include <Cuboidpch.h>
#include <glad/glad.h>
#include "OpenGLVertexArray.h"
#include "OpenGLShader.h"


namespace Cuboid
{


	OpenGLVertexArray::OpenGLVertexArray()
	{
		glGenVertexArrays(1, &m_RendererID);

	}

	void OpenGLVertexArray::Bind() const
	{
		glBindVertexArray(m_RendererID);
	}

	void OpenGLVertexArray::UnBind() const
	{
		glBindVertexArray(0);
	}

	OpenGLVertexArray::~OpenGLVertexArray()
	{
		glDeleteVertexArrays(1, &m_RendererID);
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
		const auto& elements = vtxBuffer->GetBufferLayout().GetElements();

		uint32_t attrib = 0;

		for (int i = 0; i < elements.size(); i++)
		{
			auto& element = elements[i];
			attrib = (uint32_t)std::dynamic_pointer_cast<OpenGLShader>(m_Shader)->GetAttributeLocation(element.Name);

            CUBOID_CORE_INFO("attrib location {0} attrib name {1} ",attrib, element.Name);

			glEnableVertexAttribArray(attrib);
			glVertexAttribPointer(attrib,
                                  element.GetComponentCount(),
                                  ShaderDataTypeToOpenGLBaseType(element.Type),
                                  (GLboolean)(element.Normalized ? GL_TRUE : GL_FALSE),
                                  vtxBuffer->GetBufferLayout().GetStride(),
                                  (const void*)element.Offset);


		}
	}

	GLenum OpenGLVertexArray::ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
	{

		switch(type){

			case ShaderDataType::Float1:    return GL_FLOAT;
			case ShaderDataType::Float2:   return GL_FLOAT;
			case ShaderDataType::Float3:   return GL_FLOAT;
			case ShaderDataType::Float4:   return GL_FLOAT;
			case ShaderDataType::Mat3:     return GL_FLOAT;
			case ShaderDataType::Mat4:     return GL_FLOAT;
			case ShaderDataType::Int:      return GL_INT;
			case ShaderDataType::Int2:     return GL_INT;
			case ShaderDataType::Int3:     return GL_INT;
			case ShaderDataType::Int4:     return GL_INT;
			case ShaderDataType::Bool:     return GL_BOOL;

		}
		//TODO: Handle Errors here
		return 0;
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

    void OpenGLVertexArray::AddVertexBuffer(const Ref<VertexBuffer> &vtxBuffer)
    {

        Bind();
        vtxBuffer->Bind();
        const auto& elements = vtxBuffer->GetBufferLayout().GetElements();
        uint32_t attrib = 0;

        for (int i = 0; i < elements.size(); i++)
        {
            auto& element = elements[i];
            attrib = (uint32_t)std::dynamic_pointer_cast<OpenGLShader>(m_Shader)->GetAttributeLocation(element.Name);
            CUBOID_CORE_INFO("attrib location {0} attrib name {1} ",attrib, element.Name);
            glEnableVertexAttribArray(attrib);
            glVertexAttribPointer(attrib,
                                  element.GetComponentCount(),
                                  ShaderDataTypeToOpenGLBaseType(element.Type),
                                  (GLboolean)(element.Normalized ? GL_TRUE : GL_FALSE),
                                  vtxBuffer->GetBufferLayout().GetStride(),
                                  (const void*)element.Offset);
        }

    }

}
