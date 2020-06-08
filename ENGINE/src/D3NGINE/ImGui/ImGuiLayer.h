#if _MSVC
#pragma once
#endif


#include "D3NGINE/Core/Layer.h"

#ifndef IMGUILAYER_H
#define IMGUILAYER_H

namespace D3G
{
	typedef union SDL_Event SDL_Event;
	class ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer() override;
		void OnImGuiRender() override;
		void OnEvent(SDL_Event* event) override;
		void OnAttach() override;
		void OnDetach() override;
		void Begin();
		void End();
	};

}

#endif
