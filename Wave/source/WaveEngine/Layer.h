#ifndef LAYER_H
#define LAYER_H

#include "Core.h"
#include "Events/Event.h"

namespace wave {


	class WAVE_API Layer {

		template<typename OStream>
		friend OStream& operator<<(OStream& os, const Layer& layer) {
//
			return os << layer.GetName();
		}

		//template<typename OStream>
		//friend OStream& operator<<(OStream& os, const Layer* layer) {
		//	
		//	return os << layer->GetName();
		//}

	public:
		Layer(std::string name);
		virtual ~Layer();

		virtual void OnAttach() {}
		virtual void OnDettach() {}
		virtual void OnUpdate() {}
		virtual void OnImGuiRender() {}
		virtual void OnEvent(Event& e) {}

		std::string GetName() const { return m_Name; }

	protected:
		std::string m_Name;
	};


	inline std::ostream& operator<<(std::ostream& os, const Layer& layer) {

		return os << layer.GetName();
	}

} // namespace wave

#endif