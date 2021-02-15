/*
 * GraphicsContext.h
 *
 *  Created on: 26 May,2020
 *      Author: Jerry
 */

#ifndef ENGINE_SRC_CUBOID_RENDERER_GRAPHICSCONTEXT_H_
#define ENGINE_SRC_CUBOID_RENDERER_GRAPHICSCONTEXT_H_

#include <any>
#include "Cuboid/Core/Core.h"

namespace Cuboid
{
	class GraphicsContext
	{
		public:
			virtual void Init() = 0;
			virtual void SwapBuffers() = 0;
			virtual ~GraphicsContext() = default;
			virtual void SetVsync(bool enable) = 0;
			virtual void ResizeSwapBuffers() = 0;
			static Scope<GraphicsContext> Create(std::any window);
	};

} /* namespace Cuboid */

#endif /* ENGINE_SRC_CUBOID_RENDERER_GRAPHICSCONTEXT_H_ */
