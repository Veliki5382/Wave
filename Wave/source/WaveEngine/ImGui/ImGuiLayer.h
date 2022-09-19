#ifndef IMGUI_LAYER_H
#define IMGUI_LAYER_H

#include "WaveEngine/Layer.h"
#include "WaveEngine/Events/MouseEvent.h"
#include "WaveEngine/Events/KeyEvent.h"
#include "WaveEngine/Events/ApplicationEvent.h"


namespace wave {


	class WAVE_API ImGuiLayer : public Layer {

	public:
		ImGuiLayer();
		~ImGuiLayer();

		void OnAttach() override;
		void OnDettach() override;
		void OnImGuiRender() override;

		void Begin();
		void End();

	private:
		double m_Time = 0.0f;

	};

} // namespace wave

#endif