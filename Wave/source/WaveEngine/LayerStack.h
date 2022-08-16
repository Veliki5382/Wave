#ifndef LAYERSTACK_H
#define LAYERSTACK_H

#include "Layer.h"

namespace wave {

	
	class WAVE_API LayerStack {

	public:
		LayerStack();
		virtual ~LayerStack();

		void Push(Layer* layer);
		void Pop(Layer* layer);

		std::vector<Layer*>::iterator begin() { return m_LayerStack.begin(); }
		std::vector<Layer*>::iterator end() { return m_LayerStack.end(); }

		std::vector<Layer*>::const_iterator const_begin() const { return m_LayerStack.begin(); }
		std::vector<Layer*>::const_iterator const_end() const { return m_LayerStack.end(); }

		size_t size() const { return m_LayerStack.size(); }

		Layer* operator[](int index) { return m_LayerStack[index]; }
		
	private:
		std::vector<Layer*> m_LayerStack;
		std::vector<Layer*>::iterator m_LayerPointer;
	};

} // namespace wave



#endif