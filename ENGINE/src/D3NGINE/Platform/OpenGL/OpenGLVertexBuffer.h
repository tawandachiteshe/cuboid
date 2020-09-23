#include <D3NGINE/Renderer/Buffer.h>

#ifndef D3G_OPENGLVERTEXBUFFER_H
#define D3G_OPENGLVERTEXBUFFER_H
namespace D3G
{


	class OpenGLVertexBuffer : public VertexBuffer
	{

	private:
		unsigned int m_RendererID;

		BufferLayout m_Layout;

	public:
		
		const BufferLayout& GetBufferLayout() const override;

		OpenGLVertexBuffer(void* vertices, uint32_t size);

		OpenGLVertexBuffer(uint32_t size);

		virtual void Bind() const override;

		virtual void UnBind() const override;

		virtual void SetLayout(const BufferLayout& layout) override;

		OpenGLVertexBuffer();

		~OpenGLVertexBuffer();

		void SetData(const void *data, uint32_t size) override;
	};

}

#endif
