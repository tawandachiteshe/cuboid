#ifndef D3G_OPENGLCOMMON_H
#define D3G_OPENGLCOMMON_H

namespace D3G
{

#define ThrowIfError(x) GLClearErrors();\
		x; \
		D3G_ASSERT(GLLogCall(#x, __FILE__, __LINE__),"")

	void GLClearErrors();

	bool GLLogCall(const char* function, const char* file, int line);

}


#endif
