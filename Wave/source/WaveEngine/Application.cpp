#include "wavepch.h"
#include "Application.h"

#include "Events/ApplicationEvent.h"
#include "Events/MouseEvent.h"
#include "Platform/Windows/WindowsWindow.h"
#include "WaveEngine/Input.h"

#include <GLAD/glad.h>

namespace wave {

	Application* Application::s_Instance = nullptr;

	Application::Application() {
		WAVE_CORE_ASSERT(!s_Instance, "There is already application instance constructed!");
		s_Instance = this;
		m_Window = Window::Create(WindowProps("Wave", 1280, 720));
		m_Running = true;
		m_Window->SetEventCallbackFunction(WAVE_BIND_FN(Application::onEvent));
	}
	Application::~Application() {
		delete m_Window;
	}

	void Application::onEvent(Event& e) {
		
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowClosedEvent>(WAVE_BIND_FN(Application::windowClosed));
		
		//WAVE_CORE_TRACE("{0}", e);

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
		

		// ------------ MAIN WHILE LOOP ------------------------------------
		while (m_Running) {

			for (auto it = m_LayerStack.begin(); it != m_LayerStack.end(); ++it) {
				(*it)->OnUpdate();
			}

			//auto pos = Input::GetMousePosition();
			//WAVE_CORE_TRACE("{0}, {1}", pos.first, pos.second);

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