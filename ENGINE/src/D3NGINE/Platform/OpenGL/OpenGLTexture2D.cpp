#include <d3gpch.h>
#include "OpenGLTexture2D.h"
#include <D3NGINE/utils/stb_image/stb_image.h>
#include <glad/glad.h>


namespace D3G
{


	OpenGLTexture2D::OpenGLTexture2D(uint32_t width, uint32_t height, uint32_t levels)
	: m_Width(width), m_Height(height), m_Filepath("")
	{
        D3G_CORE_INFO("Raw image data {0} {1}", m_Width, m_Height);

		m_InternalFormat = GL_RGBA8;
		m_DataFormat = GL_RGBA;

		uint32_t _width = m_Width;
		uint32_t _height = m_Height;

		glGenTextures(1, &m_RendererID);
		glBindTexture(GL_TEXTURE_2D, m_RendererID);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

        uint32_t RawImageData = 0xffffffff;
        glTexImage2D(GL_TEXTURE_2D, 0, m_InternalFormat, m_Width, m_Height, 0, m_DataFormat, GL_UNSIGNED_BYTE, &RawImageData);

        glBindTexture(GL_TEXTURE_2D, 0);

	}


	OpenGLTexture2D::OpenGLTexture2D(const std::string& filePath) :
							m_Filepath(filePath)
	{
		int width, height, channels;
		stbi_set_flip_vertically_on_load(1);
		stbi_uc* data = stbi_load(m_Filepath.c_str(), &width, &height, &channels, 0);

		D3G_ASSERT(data, "Texture Could not be loaded! ");
		D3G_CORE_INFO("Data {0} {1} {2} {3}", width, height, channels, m_Filepath);

		GLenum internalFormat = 0, dataFormat = 0;
		if (channels == 4)
		{
			internalFormat = GL_RGBA8;
			dataFormat = GL_RGBA;
		}
		else if (channels == 3)
		{
			internalFormat = GL_RGB8;
			dataFormat = GL_RGB;
		}

		m_InternalFormat = internalFormat;
		m_DataFormat = dataFormat;

		D3G_CORE_INFO("image dada {0} {1}", m_InternalFormat, m_DataFormat);
		glGenTextures(1, &m_RendererID);
		glBindTexture(GL_TEXTURE_2D, m_RendererID);
		m_Width = width;
		m_Height = height;
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glTexImage2D(GL_TEXTURE_2D, 0, m_InternalFormat, m_Width, m_Height, 0, m_DataFormat, GL_UNSIGNED_BYTE, data);
		glBindTexture(GL_TEXTURE_2D, 0);

		if (data)
			stbi_image_free(data);
	}



	OpenGLTexture2D::~OpenGLTexture2D()
	{
		glDeleteTextures(1, &m_RendererID);
	}

	void OpenGLTexture2D::SetData(void *data, uint32_t size)
	{
		uint32_t bpp = m_DataFormat == GL_RGBA ? 4 : 3;
		//D3G_CORE_ASSERT(size == (m_Width * m_Height * bpp), "Data must be entire texture!");
        
        glBindTexture(GL_TEXTURE_2D, m_RendererID);
        glTexImage2D(GL_TEXTURE_2D, 0, m_InternalFormat, m_Width, m_Height, 0, m_DataFormat, GL_UNSIGNED_BYTE, data);
	}

	void* OpenGLTexture2D::GetTextureID()
	{
		return &m_RendererID;
	}

	void OpenGLTexture2D::Bind(unsigned int slot) const
	{
		glActiveTexture(GL_TEXTURE0 + slot);
		glBindTexture(GL_TEXTURE_2D, m_RendererID);
	}

}
