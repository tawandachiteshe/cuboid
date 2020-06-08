#include "BufferLayout.h"

#ifndef D3G_RENDERER_BUFFER_H
#define D3G_RENDERER_BUFFER_H

namespace D3G
{


	enum class ShaderDataType
	{

		Float1 = 1,
		Float2 = 2,
		Float3 = 3,
		Float4 = 4
	};
	typedef std::vector<std::pair<ShaderDataType, std::string>> ShaderMap;

	struct VertexLayout
	{
		ShaderDataType dataSize;
		std::string attributeName;

	};

	class IndexBuffer
	{
	public:
		virtual void Bind() const = 0;
		virtual void UnBind() const = 0;
		static Ref<IndexBuffer> Create(uint32_t* indices, uint32_t size);
		virtual uint32_t GetCount() const = 0;
		virtual ~IndexBuffer() = default;
	};

	class VertexBuffer
	{
		public:
			virtual void Bind() const = 0;
			virtual void UnBind() const = 0;
			virtual void SetLayOut(const std::vector<VertexLayout>& layout) = 0;
			virtual void SetData(const void* data, uint32_t size) = 0;
			virtual const Ref<BufferLayout> GetBufferLayout() const = 0;
			static Ref<VertexBuffer> Create(float* vertices, uint32_t size);
			static Ref<VertexBuffer> Create(uint32_t size = 0);
			virtual const Ref<ShaderMap>& GetBufferLayoutData() const = 0;

			virtual ~VertexBuffer() = default;

	};


}


#endif
