#include <D3NGINE/Renderer/VertexArray.h>
#include <D3NGINE/Platform/OpenGL/common.h>
#include <D3NGINE/Platform/OpenGL/OpenGLBufferLayout.h>
#include <D3NGINE/Renderer/Buffer.h>
#include <D3NGINE/Renderer/Shader.h>

#ifndef D3G_OPENGLVERTEXARRAY_H
#define D3G_OPENGLVERTEXARRAY_H
namespace D3G
{
	class OpenGLVertexArray : public VertexArray
	{

	private:
		unsigned int m_RendererID;
		Ref<IndexBuffer> m_IdxBuffer;
		Ref<Shader> m_Shader;

	public:
		OpenGLVertexArray();
		~OpenGLVertexArray();

		 void AddVertexBuffer(const Ref<VertexBuffer>& vtxBuffer) const ;
		 void SetIndexBuffer(const  Ref<IndexBuffer>& idxBuffer);

		 void Bind() const ;
		 void UnBind() const ;

		 const Ref<IndexBuffer>& GetIndexBuffer() const ;

		virtual void SetShader(const Ref<Shader> &mShader) override;
	};
}

#endif
