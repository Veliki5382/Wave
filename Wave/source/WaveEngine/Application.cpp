#include "wavepch.h"
#include "Application.h"

#include "Events/ApplicationEvent.h"
#include "Events/MouseEvent.h"
#include "Platform/Windows/WindowsWindow.h"

namespace wave {

	Application::Application() {
		m_Window = Window::Create();
		m_Running = true;
		m_Window->SetEventCallbackFunction(std::bind(&Application::onEvent, this, std::placeholders::_1));
	}
	Application::~Application() {
		delete m_Window;
	}

	void Application::onEvent(Event& e) {
		
		EventDispatcher dispatcer(e);
		dispatcer.Dispatch<WindowClosedEvent>(std::bind(&Application::windowClosed, this, std::placeholders::_1));
		
		WAVE_CORE_TRACE("{0}", e);
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

	bool Application::windowClosed(WindowClosedEvent& e) {

		m_Running = false;
		return true;
	}

} // namespace wave