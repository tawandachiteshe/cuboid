#if _MSVC
#pragma once
#endif


#include "Cuboid/Core/Layer.h"
#include "Cuboid/Events/Event.h"

#ifndef IMGUILAYER_H
#define IMGUILAYER_H

namespace Cuboid
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
