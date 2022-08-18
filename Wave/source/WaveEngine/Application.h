#ifndef APPLICATION_H
#define APPLICATION_H

//#include "source/wavepch.h"
#include "Core.h"
#include "LayerStack.h"
#include "Platform/Windows/WindowsWindow.h"
#include "Events/ApplicationEvent.h"

namespace wave {

	class WAVE_API Application {
	public:

		Application();
		virtual ~Application();

		void Run();
		void onEvent(Event& e);

		void PushLayer(Layer* layer);

		inline Window* GetWindow() { return m_Window; }
		inline static Application* Get() { return s_Instance; }

	private:
		bool windowClosed(WindowClosedEvent& e);
		
		Window* m_Window;
		bool m_Running;
		LayerStack m_LayerStack;
	
	private:
		static Application* s_Instance;
	};

	
	// ----- For user to define -----------
	
	Application* CreateApplication();

} // namespace wave

#endif