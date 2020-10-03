#include <d3gpch.h>
#include <D3NGINE/Renderer/RendererAPI.h>
#include <D3NGINE/Renderer/Texture.h>
#include <D3NGINE/Platform/OpenGL/OpenGLTexture2D.h>
#include <D3NGINE/Platform/DirectX/Renderer/D3DTexture.h>

namespace D3G
{

	Ref<Texture2D> Texture2D::Create(uint32_t width, uint32_t height, uint32_t textureArraySize)
	{
		switch (RendererAPI::GetAPI())
		{
		case RendererAPI::API::None:    D3G_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::Opengl:  return CreateRef<OpenGLTexture2D>(width, height, 0);
		case RendererAPI::API::DirectX: return CreateRef<D3DTexture>(width, height, textureArraySize);
		}

		return nullptr;
	}

	Ref<Texture2D> Texture2D::Create(const std::string& path, uint32_t textureArraySize)
	{
		switch (RendererAPI::GetAPI())
		{
		case RendererAPI::API::None:    D3G_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::Opengl:  return CreateRef<OpenGLTexture2D>(path);
		case RendererAPI::API::DirectX: return CreateRef<D3DTexture>(path.c_str(), textureArraySize);
		}

		return nullptr;
	}

} /* namespace D3G */
