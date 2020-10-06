#include <Cuboidpch.h>
#include <Cuboid/Renderer/RendererAPI.h>
#include <Cuboid/Renderer/Texture.h>
#include <Cuboid/Platform/OpenGL/OpenGLTexture2D.h>
#include <Cuboid/Platform/DirectX/Renderer/D3DTexture.h>

namespace Cuboid
{

	Ref<Texture2D> Texture2D::Create(uint32_t width, uint32_t height, uint32_t textureArraySize)
	{
		switch (RendererAPI::GetAPI())
		{
		case RendererAPI::API::None:    CUBOID_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::Opengl:  return CreateRef<OpenGLTexture2D>(width, height, 0);
		case RendererAPI::API::DirectX: return CreateRef<D3DTexture>(width, height, textureArraySize);
		}

		return nullptr;
	}

	Ref<Texture2D> Texture2D::Create(const std::string& path, uint32_t textureArraySize)
	{
		switch (RendererAPI::GetAPI())
		{
		case RendererAPI::API::None:    CUBOID_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::Opengl:  return CreateRef<OpenGLTexture2D>(path);
		case RendererAPI::API::DirectX: return CreateRef<D3DTexture>(path.c_str(), textureArraySize);
		}

		return nullptr;
	}

} /* namespace Cuboid */
