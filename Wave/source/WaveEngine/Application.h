#ifndef APPLICATION_H
#define APPLICATION_H

//#include "source/wavepch.h"
#include "Core.h"
#include "Platform/Windows/WindowsWindow.h"
#include "Events/ApplicationEvent.h"

namespace wave {

	class WAVE_API Application {
	public:

		Application();
		virtual ~Application();

		void Run();
		
		void onEvent(Event& e);

	private:
		bool windowClosed(WindowClosedEvent& e);
		
		Window* m_Window;
		bool m_Running;
	};

	
	// ----- For user to define -----------
	
	Application* CreateApplication();

} // namespace wave

#endif