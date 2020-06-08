#include <D3NGINE/Renderer/Texture.h>


#ifndef D3G_OPENGL_TEXTURE2D_H
#define D3G_OPENGL_TEXTURE2D_H

namespace D3G
{


	class OpenGLTexture2D : public Texture2D
	{

		private:
			uint32_t				m_RendererID = 0;
			std::string				m_Filepath = NULL;
			uint32_t				m_Height = 0;
			uint32_t				m_Width = 0;
			uint32_t m_InternalFormat, m_DataFormat = 0;
		public:
			OpenGLTexture2D(uint32_t width, uint32_t height, uint32_t levels = 0);
			OpenGLTexture2D(const std::string& filePath);
			virtual ~OpenGLTexture2D();

			virtual uint32_t GetWidth() const override { return m_Width; }
			virtual uint32_t GetHeight() const override { return m_Height; }

			virtual void SetData(void* data, uint32_t size) override;

			virtual void Bind(uint32_t slot = 0) const override;


			virtual bool operator==(const Texture& other) const override
			{
				return m_RendererID == ((OpenGLTexture2D&)other).m_RendererID;
			}
	};

}

#endif
