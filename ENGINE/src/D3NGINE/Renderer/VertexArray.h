#include  "Shader.h"
#include "Buffer.h"

#ifndef D3G_RENDERER_VERTEXARRAY_H
#define D3G_RENDERER_VERTEXARRAY_H
namespace D3G
{
	class VertexArray
	{
	public:
		virtual void Bind() const = 0;

		virtual void UnBind() const = 0;

		virtual const Ref<IndexBuffer>& GetIndexBuffer() const = 0;

		virtual void AddVertexBuffer(const Ref<VertexBuffer>& vtxBuffer) const = 0;

		virtual void AddVertexBuffer(const Ref<VertexBuffer>& vtxBuffer) = 0;

		virtual void SetIndexBuffer(const Ref<IndexBuffer>& idxBuffer) = 0;

		virtual void SetShader(const Ref<Shader> &mShader) = 0;

		static Ref<VertexArray> Create();

		virtual ~VertexArray() = default;
	};
}

#endif
