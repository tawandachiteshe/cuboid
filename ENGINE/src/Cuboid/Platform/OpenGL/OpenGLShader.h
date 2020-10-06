#include <Cuboid/Renderer/Shader.h>
#include <glm/glm.hpp>

#ifndef CUBOID_OPENGLSHADER_H
#define CUBOID_OPENGLSHADER_H
namespace Cuboid
{

	class OpenGLShader : public Shader
	{

		private:
			unsigned int m_Program;
			unsigned int m_Shaderid;
			void CreateShaders(const std::string& fragShader, const std::string& vertShader);
			unsigned int CompileShader(const std::string& src, unsigned int shaderType);
			enum{
				POSITION_ATTRIBUTE = 0,
				COLOR_ATTRIBUTE,
				NORMAL_ATTRIBUTE,
				TEXCOORD_ATTRIBUTE
			};

		public:
			OpenGLShader(const std::string& fragShader, const std::string& vertShader);
			virtual ~OpenGLShader();
			void bindDefaultAttributes() const;
			void bindAttribute(uint32_t location, const std::string& name) const;
			int GetUniformLocation(const std::string& name) const;
			inline uint32_t GetShaderProgramID() const { return m_Program; }

			int GetAttributeLocation(const std::string& name);


			virtual void SetInt(const std::string& name, int value) override;
			virtual void SetIntArray(const std::string& name, int* values, uint32_t count) override;
			virtual void SetFloat(const std::string& name, float value) override;
			virtual void SetFloat2(const std::string& name, const glm::vec2& value) override;
			virtual void SetFloat3(const std::string& name, const glm::vec3& value) override;
			virtual void SetFloat4(const std::string& name, const glm::vec4& value) override;
			virtual void SetMat4(const std::string& name, const glm::mat4& value) override;


			virtual void Bind() override;
			virtual void UnBind() override;

			void SetUniformMatf(const std::string& name, const glm::mat4& mat) const;
	};

}

#endif
