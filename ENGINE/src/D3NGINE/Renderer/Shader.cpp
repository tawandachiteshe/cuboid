#include "Shader.h"
#include <D3NGINE/Renderer/RendererAPI.h>
#include <D3NGINE/Platform/OpenGL/OpenGLShader.h>
#include <D3NGINE/Platform/DirectX/Renderer/D3DShader.h>
#include <D3NGINE/utils/IO/FileSystem.h>

namespace D3G
{

	Ref<Shader> Shader::Create(const std::string &fragShaderSrc, const std::string &vertexShaderSrc)
	{

		switch(RendererAPI::GetAPI())
		{
		case RendererAPI::API::None: D3G_CORE_ERROR("None Currently not suppported! "); break;
		case RendererAPI::API::Opengl: return CreateRef<OpenGLShader>(fragShaderSrc, vertexShaderSrc);
		case RendererAPI::API::DirectX: return CreateRef<D3DShader>(fragShaderSrc, vertexShaderSrc);
		}
		return nullptr;
	}

	Ref <Shader> Shader::FromShaderSourceFiles(const std::string& FragShaderSrcPath, const std::string& VertShaderSrcPath)
	{
		const std::string& tempFrag = FileSystem::ReadFileAsText(FragShaderSrcPath);
		const std::string& tempVert = FileSystem::ReadFileAsText(VertShaderSrcPath);

		D3G_CORE_ASSERT(tempFrag.size(), "Frag Shader src can't be loaded");
		D3G_CORE_ASSERT(tempVert.size(), "Vert Shader src can't be loaded");

		return  Create(tempFrag, tempVert);
	}

}
