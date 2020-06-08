#include <D3NGINE/Platform/OpenGL/common.h>
#include <glad/glad.h>

namespace D3G
{
	void GLClearErrors()
	{
		while (glGetError() != GL_NO_ERROR);
	}

	bool GLLogCall(const char* function, const char* file, int line)
	{
		while (GLenum error = glGetError())
		{
			std::stringstream ss;
			ss << "[OpenGl Error] " << error <<
					" file: " << file << " :" << " line: " << line;
			D3G_CORE_ERROR(ss.str());
			return false;
		}

		return true;
	}
}
