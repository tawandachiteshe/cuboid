#include "OpenGLShader.h"
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
//TODO: Change attribute InPostion to position
//TODO: The texture uniform

namespace D3G
{

	static const std::string _COLOR_ATTRIBUTE = "color";
	static const std::string _POSITION_ATTRIBUTE = "position";
	static const std::string _NORMAL_ATTRIBUTE = "normal";
	static const std::string _TEXCOORD_ATTRIBUTE = "texcoord";


	OpenGLShader::OpenGLShader(const std::string& fragShader, const std::string& vertShader)
	{

		if (fragShader.size() == 0 && vertShader.size() == 0)
		{
			D3G_CORE_ERROR("failed to read shader from file");
			return;
		}

		CreateShaders(fragShader, vertShader);

		Bind();
		bindDefaultAttributes();
	}

	void OpenGLShader::Bind()
	{
		glUseProgram(m_Program);
	}

	void OpenGLShader::UnBind()
	{
		glUseProgram(0);
	}

	int OpenGLShader::GetUniformLocation(const std::string& name) const
	{
		GLint loc = -1;
		loc = glGetUniformLocation(m_Program, name.c_str());

		return loc;
	}

	OpenGLShader::~OpenGLShader()
	{
		glDeleteProgram(m_Program);
	}

	unsigned int OpenGLShader::CompileShader(const std::string& src, unsigned int shaderType)
	{
		m_Shaderid = glCreateShader(shaderType);
		const char* source = src.c_str();
		glShaderSource(m_Shaderid, 1, &source, nullptr);
		glCompileShader(m_Shaderid);

		int results;
		glGetShaderiv(m_Shaderid, GL_COMPILE_STATUS, &results);

		if (results == GL_FALSE)
		{
			int length;
			glGetShaderiv(m_Shaderid, GL_INFO_LOG_LENGTH, &length);

			char* message = (char*)alloca(length * sizeof(char));
			glGetShaderInfoLog(m_Shaderid, length, &length, message);

			std::stringstream ss;
			ss << "Failed To Compiled " << (shaderType == GL_VERTEX_SHADER ? "vertex" : "fragment") << " SHADER!" << std::endl
					<< message << std::endl;

			D3G_CORE_ERROR(ss.str());

			glDeleteShader(m_Shaderid);
			return 0;

		}

		return m_Shaderid;
	}

	void OpenGLShader::CreateShaders(const std::string& fragShader, const std::string& vertShader)
	{
		m_Program = glCreateProgram();
		unsigned int vs = CompileShader(vertShader, GL_VERTEX_SHADER);
		unsigned int fs = CompileShader(fragShader, GL_FRAGMENT_SHADER);

		glAttachShader(m_Program, vs);
		glAttachShader(m_Program, fs);

		glLinkProgram(m_Program);
		glValidateProgram(m_Program);

		glDetachShader(m_Program, vs);
		glDetachShader(m_Program, fs);

	}


	void OpenGLShader::bindAttribute(GLuint location, const std::string& name) const
	{
		glBindAttribLocation(m_Program, location, name.c_str());
	}

	void OpenGLShader::bindDefaultAttributes() const
	{
		bindAttribute(POSITION_ATTRIBUTE	, _POSITION_ATTRIBUTE);
		bindAttribute(COLOR_ATTRIBUTE		, _COLOR_ATTRIBUTE);
		bindAttribute(TEXCOORD_ATTRIBUTE	, _TEXCOORD_ATTRIBUTE);
		bindAttribute(NORMAL_ATTRIBUTE		, _NORMAL_ATTRIBUTE);

	}



	int OpenGLShader::GetAttributeLocation(const std::string& name)
	{
		GLint loc = -1;

		loc = glGetAttribLocation(m_Program, name.c_str());
		return loc;
	}

	void OpenGLShader::SetInt(const std::string &name, int value)
	{
		int loc = glGetUniformLocation(m_Program, name.c_str());
		if (loc == -1)
			D3G_CORE_ERROR("Uniform not found");

		glUniform1i(loc, value);
	}

	void OpenGLShader::SetIntArray(const std::string &name, int *values,
			uint32_t count)
	{
		GLint location = glGetUniformLocation(m_Program, name.c_str());
		D3G_CORE_ASSERT(location, "SetArray Uniform could not be found");
		glUniform1iv(location, count, values);
	}

	void OpenGLShader::SetFloat(const std::string &name, float value)
	{
		int loc = glGetUniformLocation(m_Program, name.c_str());
		if (loc == -1)
			D3G_CORE_ERROR("Uniform not found");

		glUniform1f(loc, value);
	}

	void OpenGLShader::SetFloat2(const std::string &name,
			const glm::vec2 &value)
	{
		int loc = glGetUniformLocation(m_Program, name.c_str());
		if (loc == -1)
			D3G_CORE_ERROR("Uniform not found");

		glUniform2f(loc, value.x, value.y);
	}

	void OpenGLShader::SetFloat3(const std::string &name,
			const glm::vec3 &value)
	{
		int loc = glGetUniformLocation(m_Program, name.c_str());
		if (loc == -1)
			D3G_CORE_ERROR("Uniform not found");

		glUniform3f(loc, value.x, value.y, value.z);
	}

	void OpenGLShader::SetFloat4(const std::string &name,
			const glm::vec4 &value)
	{
		int loc = glGetUniformLocation(m_Program, name.c_str());
		if (loc == -1)
			D3G_CORE_ERROR("Uniform not found");

		glUniform4f(loc, value.x, value.y, value.z, value.w);
	}

	void OpenGLShader::SetMat4(const std::string &name, const glm::mat4 &value)
	{

		int loc = glGetUniformLocation(m_Program, name.c_str());

		if (loc == -1)
			D3G_CORE_ERROR("Uniform not found");

		glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(value));
	}

}
