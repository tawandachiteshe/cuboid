#if _MSVC
#pragma once
#endif


#include "D3NGINE/Core/Layer.h"
#include "D3NGINE/Events/Event.h"

#ifndef IMGUILAYER_H
#define IMGUILAYER_H

namespace D3G
{
	
	class ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer() override;
		void OnImGuiRender() override;
		void OnEvent(Event& event) override;
		void OnAttach() override;
		void OnDetach() override;
		void Begin();
		void End();
	};

}

#endif
