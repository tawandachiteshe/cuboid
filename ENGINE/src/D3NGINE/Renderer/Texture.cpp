#include <D3NGINE/Renderer/RendererAPI.h>
#include <D3NGINE/Renderer/Texture.h>
#include <D3NGINE/Platform/OpenGL/OpenGLTexture2D.h>
namespace D3G
{

	Ref<Texture2D> Texture2D::Create(uint32_t width, uint32_t height)
	{
		switch (RendererAPI::GetAPI())
		{
		case RendererAPI::API::None:    D3G_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::Opengl:  return CreateRef<OpenGLTexture2D>(width, height, 0);
		}

		return nullptr;
	}

	Ref<Texture2D> Texture2D::Create(const std::string& path)
	{
		switch (RendererAPI::GetAPI())
		{
		case RendererAPI::API::None:    D3G_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::Opengl:  return CreateRef<OpenGLTexture2D>(path);
		}

		return nullptr;
	}

} /* namespace D3G */
