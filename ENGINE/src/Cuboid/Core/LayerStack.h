#include <vector>
#include "Layer.h"


#ifndef CUBOID_LAYERSTACK_H
#define CUBOID_LAYERSTACK_H


namespace Cuboid
{
	class LayerStack
	{
	public:
		LayerStack() = default;
		~LayerStack();

		void PushLayer(Layer* layer);
		void PopLayer(Layer* layer);

		void PushOverLay(Layer* overlay);
		void PopOverLay(Layer* overlay);

		std::vector<Layer*>::iterator begin() { return m_Layers.begin(); }
		std::vector<Layer*>::iterator end()  { return m_Layers.end(); }
		std::vector<Layer*>::reverse_iterator rbegin() { return m_Layers.rbegin(); }
		std::vector<Layer*>::reverse_iterator rend() { return m_Layers.rend(); }

	private:

		std::vector<Layer*> m_Layers;
		unsigned int m_LayerInsertIndex = 0;

	};
}


#endif
