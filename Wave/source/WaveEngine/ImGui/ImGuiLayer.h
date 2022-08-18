#ifndef IMGUI_LAYER_H
#define IMGUI_LAYER_H

#include "WaveEngine/Layer.h"

namespace wave {


	class WAVE_API ImGuiLayer : public Layer {

	public:
		ImGuiLayer();
		~ImGuiLayer();

		void OnAttach() override;
		void OnDettach() override;
		void OnUpdate() override;
		void OnEvent(Event& e) override;

	private:
		
	};

} // namespace wave

#endif