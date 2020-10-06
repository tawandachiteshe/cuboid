
#include <Cuboid/Renderer/Buffer.h>


#ifndef CUBOID_OPENGLINDEXBUFFER_H
#define CUBOID_OPENGLINDEXBUFFER_H


namespace Cuboid
{

	class OpenGLIndexBuffer : public IndexBuffer
	{

	private:

		unsigned int m_RendererID;
		const uint32_t m_Count;
	public:
		OpenGLIndexBuffer(uint32_t* indices, uint32_t size);
		virtual void Bind() const override;
		virtual void UnBind() const override;
		~OpenGLIndexBuffer();
		virtual uint32_t GetCount() const override;
	};

}


#endif
