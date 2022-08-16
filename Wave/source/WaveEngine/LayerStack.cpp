#include "wavepch.h"
#include "LayerStack.h"

namespace wave {

	
	LayerStack::LayerStack() {
		m_LayerPointer = m_LayerStack.begin();
	}

	LayerStack::~LayerStack() {
		for (auto it = m_LayerStack.begin(); it != m_LayerStack.end(); ++it) {
			delete* it;
		}
		m_LayerStack.clear();
	}

	void LayerStack::Push(Layer* layer) {
		m_LayerStack.push_back(layer);
		//m_LayerPointer++;
	}

	void LayerStack::Pop(Layer* layer) {
		std::vector<Layer*>::iterator ptr;
		for (ptr = m_LayerStack.begin(); ptr != m_LayerStack.end(); ++ptr) {
			if (*ptr == layer) {
				m_LayerStack.erase(ptr);
				m_LayerPointer--;
				break;
			}
		}
		if (ptr == m_LayerStack.end()) {
			WAVE_WARN("Layer {0} doesn't exist.", *layer);
		}

		//m_LayerStack.erase()
	}

} // namespace wave