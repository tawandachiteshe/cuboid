#include <D3NGINE/Platform/OpenGL/common.h>
#include <glad\glad.h>
#include <D3NGINE/Renderer/BufferLayout.h>

#ifndef D3G_OPENGLBUFFER_LAYOUT_H
#define D3G_OPENGLBUFFER_LAYOUT_H

namespace D3G
{

	struct OpenGLVertexBufferElement : VertexBufferElement
	{
		unsigned int type;
		unsigned int count;
		unsigned char normalized;

		static unsigned int GetSizeOfType(unsigned int size)
		{
			switch (size)
			{
			case GL_FLOAT:			return 4;
			case GL_UNSIGNED_INT:	return 4;
			case GL_UNSIGNED_BYTE:	return 1;

			}
			D3G_ASSERT(false,"");
			return 0;
		}

	};

	class OpenGLBufferLayout : public BufferLayout
	{

	private:
		std::vector<OpenGLVertexBufferElement> m_ElementLayouts;
		unsigned int m_Stride;


	public:
		OpenGLBufferLayout();

		virtual ~OpenGLBufferLayout();

		template<typename T>
		void Push(unsigned int count);



		virtual Ref<std::vector<VertexBufferElement>> GetElements() const override;
		virtual uint32_t GetStride() const override;
	};

}

#endif
