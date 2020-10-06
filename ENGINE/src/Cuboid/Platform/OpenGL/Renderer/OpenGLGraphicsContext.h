/*
 * OpenGLGraphicsContext.h
 *
 *  Created on: 26 May,2020
 *      Author: Jerry
 */




#ifndef ENGINE_SRC_CUBOID_PLATFORM_OPENGL_RENDERER_OPENGLGRAPHICSCONTEXT_H_
#define ENGINE_SRC_CUBOID_PLATFORM_OPENGL_RENDERER_OPENGLGRAPHICSCONTEXT_H_


#include <Cuboid/Renderer/GraphicsContext.h>

typedef struct SDL_Window SDL_Window;

namespace Cuboid
{

	class OpenGLGraphicsContext : public GraphicsContext
	{
		public:
			OpenGLGraphicsContext(SDL_Window* window);
			virtual ~OpenGLGraphicsContext();
			virtual void Init() override;
			virtual void SetVsync(bool enable) override;
			virtual void SwapBuffers() override;

			uint32_t SDL_WINDOW_OPENGL = 0x00000002;
            inline void* GetContext() { return m_Context; }

		void ResizeSwapBuffers() override;

		private:
            void* m_Context;
			SDL_Window *m_Window;
	};

} /* namespace Cuboid */

#endif /* ENGINE_SRC_CUBOID_PLATFORM_OPENGL_RENDERER_OPENGLGRAPHICSCONTEXT_H_ */
