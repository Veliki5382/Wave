#include "wavepch.h"
#include "LayerStack.h"

namespace wave {

	
	LayerStack::LayerStack() {
		m_LayerIndex = 0;
	}

	LayerStack::~LayerStack() {
		for (auto it = m_LayerStack.begin(); it != m_LayerStack.end(); ++it) {
			delete* it;
		}
		m_LayerStack.clear();
	}

	void LayerStack::PushLayer(Layer* layer, unsigned int index) {
		
		WAVE_ASSERT(layer != nullptr, "Instance of {0} wasn't properly made before calling attaching to layerstack.");
		if (index == -1) {
			m_LayerStack.push_back(layer);
		}
		else {
			WAVE_ASSERT(index >= 0, "Index isn't valid.");
			m_LayerStack.emplace(m_LayerStack.begin() + index, layer);
		}
		layer->OnAttach();
		m_LayerIndex++;
	}

	void LayerStack::PopLayer(Layer* layer) {
		std::vector<Layer*>::iterator ptr;
		for (ptr = m_LayerStack.begin(); ptr != m_LayerStack.end(); ++ptr) {
			if (*ptr == layer) {
				(*ptr)->OnDettach();
				m_LayerStack.erase(ptr);
				m_LayerIndex--;
				break;
			}
		}
		if (ptr == m_LayerStack.end()) {
			WAVE_WARN("Layer {0} doesn't exist.", *layer);
		}

		//m_LayerStack.erase()
	}

} // namespace wave