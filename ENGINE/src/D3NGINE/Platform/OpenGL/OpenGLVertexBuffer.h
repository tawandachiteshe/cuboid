#include <D3NGINE/Renderer/Buffer.h>
#include <D3NGINE/Platform/OpenGL/OpenGLBufferLayout.h>
#include <D3NGINE/Renderer/BufferLayout.h>


#ifndef D3G_OPENGLVERTEXBUFFER_H
#define D3G_OPENGLVERTEXBUFFER_H
namespace D3G
{


	class OpenGLVertexBuffer : public VertexBuffer
	{

	private:
		unsigned int m_RendererID;
		Ref<ShaderMap> m_LayOutData;

		Ref<OpenGLBufferLayout> m_Layout;


	public:

		const Ref<ShaderMap>& GetBufferLayoutData() const override;
		const Ref<BufferLayout> GetBufferLayout() const override;

		OpenGLVertexBuffer(float* vertices, uint32_t size);
		OpenGLVertexBuffer(uint32_t size);
		virtual void Bind() const override;
		virtual void UnBind() const override;
		virtual void SetLayOut(const std::vector<VertexLayout>& layout) override;
		OpenGLVertexBuffer();
		~OpenGLVertexBuffer();

		void SetData(const void *data, uint32_t size) override;
	};

}

#endif
