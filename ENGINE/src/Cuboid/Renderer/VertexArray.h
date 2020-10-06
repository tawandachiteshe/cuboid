#include  "Shader.h"
#include "Buffer.h"

#ifndef CUBOID_RENDERER_VERTEXARRAY_H
#define CUBOID_RENDERER_VERTEXARRAY_H
namespace Cuboid
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
