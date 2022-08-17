#include "wavepch.h"
#include "Application.h"

#include "Events/ApplicationEvent.h"
#include "Events/MouseEvent.h"
#include "Platform/Windows/WindowsWindow.h"

#include <GLAD/glad.h>

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
		
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowClosedEvent>(std::bind(&Application::windowClosed, this, std::placeholders::_1));
		
		WAVE_CORE_TRACE("{0}", e);

		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin(); ) {
			(*--it)->OnEvent(e);
			if (e.Handled()) {
				break;
			}
		}
	}

	void Application::PushLayer(Layer* layer) {
		m_LayerStack.Push(layer);
	}

	void Application::Run() {
		//WindowResizedEvent e(6436436, 46);
		//WAVE_TRACE(e);
		//MouseMovedEvent vent(250, 620);
		//WAVE_TRACE(vent);

		gladLoadGL();

		while (m_Running) {

			for (auto it = m_LayerStack.begin(); it != m_LayerStack.end(); ++it) {
				(*it)->OnUpdate();
			}

			m_Window->OnUpdate();
			glClearColor(1, 1, 0, 1);
			glClear(unsigned int(GL_COLOR_BUFFER_BIT));
			
		}
	}

	bool Application::windowClosed(WindowClosedEvent& e) {

		m_Running = false;
		return true;
	}

} // namespace wave