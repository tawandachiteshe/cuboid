#include <glm/glm.hpp>


#ifndef CUBOID_RENDERER_SHADER_H
#define CUBOID_RENDERER_SHADER_H

namespace Cuboid
{

	class Shader
	{
		public:
			virtual void Bind() = 0;

			virtual void UnBind() = 0;

			virtual ~Shader() = default;

			virtual void SetInt(const std::string& name, int value) = 0;

			virtual void SetIntArray(const std::string& name, int* values, uint32_t count) = 0;

			virtual void SetPointerArray(const std::string& name, void* values, uint32_t count) {}

			virtual void SetFloat(const std::string& name, float value) = 0;

			virtual void SetFloat2(const std::string& name, const glm::vec2& value) = 0;

			virtual void SetFloat3(const std::string& name, const glm::vec3& value) = 0;

			virtual void SetFloat4(const std::string& name, const glm::vec4& value) = 0;

			virtual void SetMat4(const std::string& name, const glm::mat4& value) = 0;

			static Ref<Shader> Create(const std::string&  fragShaderSrc, const std::string& vertexShaderSrc);

			static Ref<Shader> FromShaderSourceFiles(const std::string& FragShaderSrcPath, const std::string& VertShaderSrcPath);
	};

}

#endif


