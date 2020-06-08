#ifndef D3G_RENDERER_RENDERER_H
#define D3G_RENDERER_RENDERER_H

namespace D3G
{
	struct VertexBufferElement
	{
		unsigned int type;
		unsigned int count;
		unsigned char normalized;
	};

	class BufferLayout
	{
	public:
		virtual uint32_t GetStride() const = 0;
		virtual Ref<std::vector<VertexBufferElement>> GetElements() const = 0;
		virtual ~BufferLayout() = default;
	};
}

#endif
