#include "wavepch.h"
#include "Application.h"

#include "Events/ApplicationEvent.h"
#include "Events/MouseEvent.h"
#include "Platform/Windows/WindowsWindow.h"

namespace wave {

	Application::Application() {
		m_Window = new WindowsWindow(WindowProps("ENGINE", 1600, 900));
		m_Running = true;
		
	}
	Application::~Application() {
		delete m_Window;
	}

	


	void Application::Run() {
		//WindowResizedEvent e(6436436, 46);
		//WAVE_TRACE(e);
		//MouseMovedEvent vent(250, 620);
		//WAVE_TRACE(vent);

		while (m_Running) {

			m_Window->OnUpdate();
			glClearColor(1, 1, 0, 1);
			glClear(GL_COLOR_BUFFER_BIT);
			
		}
	}

} // namespace wave