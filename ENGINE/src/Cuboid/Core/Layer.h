
#ifndef CUBOID_LAYER_H
#define CUBOID_LAYER_H

#include "Cuboid/Events/Event.h"

typedef union SDL_Event SDL_Event;
//TODO WRAP IN A NAMESPACE
namespace Cuboid
{
	class Layer
	{
	public:
		Layer(const std::string& name = "Layer");
		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate(float dt) {}
		virtual void OnImGuiRender(){}
		virtual void OnEvent(Event& event) {}
		virtual ~Layer();

		inline const std::string& GetName() const { return m_DebugName; }

	protected:

		std::string m_DebugName;
	};
}

#endif
