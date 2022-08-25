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
		void OnUpdate() override;
		void OnEvent(Event& e) override;

	private:
		double m_Time = 0.0f;

	private:
		bool OnMouseButtonPressedEvent(MouseButtonPressedEvent& event);
		bool OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& event);
		bool OnMouseScrolledEvent(MouseScrolledEvent& event);
		bool OnMouseMovedEvent(MouseMovedEvent& event);
		bool OnKeyTypedEvent(KeyTypedEvent& event);
		bool OnKeyPressedEvent(KeyPressedEvent& event);
		bool OnKeyReleasedEvent(KeyReleasedEvent& event);
		bool OnWindowResizedEvent(WindowResizedEvent& event);

	};

} // namespace wave

#endif