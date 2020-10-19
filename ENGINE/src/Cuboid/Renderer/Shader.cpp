#include "Shader.h"
#include <Cuboid/Renderer/RendererAPI.h>
#include <Cuboid/Platform/OpenGL/OpenGLShader.h>
#include <Cuboid/Platform/DirectX/D3DShader.h>
#include <Cuboid/utils/IO/FileSystem.h>

namespace Cuboid
{

	Ref<Shader> Shader::Create(const std::string &fragShaderSrc, const std::string &vertexShaderSrc)
	{

		switch(RendererAPI::GetAPI())
		{
		case RendererAPI::API::None: CUBOID_CORE_ERROR("None Currently not suppported! "); break;
		case RendererAPI::API::Opengl: return CreateRef<OpenGLShader>(fragShaderSrc, vertexShaderSrc);
		case RendererAPI::API::DirectX: return CreateRef<D3DShader>(fragShaderSrc, vertexShaderSrc);
		}
		return nullptr;
	}

	Ref <Shader> Shader::FromShaderSourceFiles(const std::string& FragShaderSrcPath, const std::string& VertShaderSrcPath)
	{
		const std::string& tempFrag = FileSystem::ReadFileAsText(FragShaderSrcPath);
		const std::string& tempVert = FileSystem::ReadFileAsText(VertShaderSrcPath);

		CUBOID_CORE_ASSERT(tempFrag.size(), "Frag Shader src can't be loaded");
		CUBOID_CORE_ASSERT(tempVert.size(), "Vert Shader src can't be loaded");

		return  Create(tempFrag, tempVert);
	}

}
