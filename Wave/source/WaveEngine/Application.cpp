#include "wavepch.h"
#include "Application.h"

#include "Events/ApplicationEvent.h"
#include "Events/MouseEvent.h"
#include "Platform/Windows/WindowsWindow.h"
#include "WaveEngine/Input.h"
#include "GLAD/glad.h"

#define glCall(x) glClearError();\
	x;\
	assert(!glLogCall());

static void glClearError() {
	while (true) {
		auto error = glGetError();
		if (error == GL_NO_ERROR) break;
	}
}
template<typename Type>
static Type toHex(Type number) {
	int value = 0, result = 0;
	while (number) {
		value += number % 16;
		value *= 10;
		number /= 16;
	}
	while (value) {
		result += value % 10;
		result *= 10;
		value /= 10;
	}
	return result / 10;
}
static bool glLogCall() {
	bool errorExist = false;
	while (true) {
		GLenum error = glGetError();
		if (error == GL_NO_ERROR) break;

		errorExist = true;
		std::cout << "[OpenGL error: ] " << toHex(error) << std::endl;
	}
	return errorExist;
}

namespace wave {

	Application* Application::s_Instance = nullptr;

	Application::Application() {

		WAVE_CORE_ASSERT(!s_Instance, "There is already application instance constructed!");
		s_Instance = this;
		m_Running = true;

		m_Window = std::unique_ptr<Window>(Window::Create(WindowProps("Wave", 1280, 720)));
		m_Window->SetEventCallbackFunction(WAVE_BIND_FN(Application::onEvent));

		m_ImGuiLayer = new ImGuiLayer;
		m_LayerStack.PushLayer(m_ImGuiLayer);

		WAVE_CORE_ASSERT(gladLoadGLLoader((GLADloadproc)glfwGetProcAddress), "Failed to initialize GLAD");

		glViewport(0, 0, 1280, 720);
		glCall(glEnable(GL_BLEND));

		glCall(glGenVertexArrays(1, &m_VertexArray));
		glCall(glBindVertexArray(m_VertexArray));
		
		glCall(glGenBuffers(1, &m_VertexBuffer));
		glCall(glBindBuffer(GL_ARRAY_BUFFER, m_VertexBuffer));
		float vertices[4 * 3] = {
		   -0.3f,   0.0f,   0.0f,
			0.3f,   0.0f,   0.0f,
			0.0f,  -0.5f,   0.0f,
			0.0f,   0.5f,   0.0f
		};
		glCall(glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW));
		glCall(glEnableVertexAttribArray(0));
		glCall(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0));

		glCall(glGenBuffers(1, &m_IndexBuffer));
		glCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexBuffer));
		unsigned int indices[2 * 3] = {
			0, 1, 2,
			0, 1, 3
		};
		glCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW));
		
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}

	Application::~Application() {
		
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
		m_LayerStack.PushLayer(layer);
	}

	void Application::Run() {
		

		// ------------ MAIN WHILE LOOP ------------------------------------
		while (m_Running) {
			
			glCall(glClearColor(0.2f, 0.2f, 0.2f, 1.0f));
			glCall(glClear(unsigned int(GL_COLOR_BUFFER_BIT)));

			glCall(glBindVertexArray(m_VertexArray));
			glCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexBuffer));
			//glCall(glDrawArrays(GL_TRIANGLES, 0, 3 * sizeof(unsigned int)));
			glCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0));
			
			glCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
			glCall(glBindVertexArray(0));

			for (auto it = m_LayerStack.begin(); it != m_LayerStack.end(); ++it) {
				(*it)->OnUpdate();
			}

			m_ImGuiLayer->Begin();
			for (auto layer : m_LayerStack) {
				layer->OnImGuiRender();
			}
			m_ImGuiLayer->End();

			m_Window->OnUpdate();
		}
	}

	bool Application::windowClosed(WindowClosedEvent& e) {

		m_Running = false;
		return true;
	}

} // namespace wave