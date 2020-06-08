/*
 * GraphicsContext.h
 *
 *  Created on: 26 May,2020
 *      Author: Jerry
 */

#ifndef ENGINE_SRC_D3NGINE_RENDERER_GRAPHICSCONTEXT_H_
#define ENGINE_SRC_D3NGINE_RENDERER_GRAPHICSCONTEXT_H_

namespace D3G
{
	class GraphicsContext
	{
		public:
			virtual void Init() = 0;
			virtual void SwapBuffers() = 0;
			virtual ~GraphicsContext() = default;
			virtual void SetVsync(bool enable) = 0;
			static Scope<GraphicsContext> Create(void* window);
	};

} /* namespace D3G */

#endif /* ENGINE_SRC_D3NGINE_RENDERER_GRAPHICSCONTEXT_H_ */
