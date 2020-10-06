#include <Cuboid/Renderer/VertexArray.h>
#include <Cuboid/Platform/OpenGL/common.h>
#include <Cuboid/Renderer/Buffer.h>
#include <Cuboid/Renderer/Shader.h>

#ifndef CUBOID_OPENGLVERTEXARRAY_H
#define CUBOID_OPENGLVERTEXARRAY_H

typedef unsigned int GLenum;

namespace Cuboid
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

		 void AddVertexBuffer(const Ref<VertexBuffer>& vtxBuffer) const;

		 void SetIndexBuffer(const  Ref<IndexBuffer>& idxBuffer);

		 void Bind() const;

		 void UnBind() const;

		void AddVertexBuffer(const Ref<VertexBuffer> &vtxBuffer) override;

		const Ref<IndexBuffer>& GetIndexBuffer() const;

		 virtual void SetShader(const Ref<Shader> &mShader) override;

		private:

		static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type);
	};
}

#endif
