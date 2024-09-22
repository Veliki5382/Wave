#include "wavepch.h"
#include "Application.h"

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

		glViewport(0, 0, 1280, 720);
		glCall(glEnable(GL_BLEND));

		m_VertexArray.reset(VertexArray::Create());
		m_VertexArray->Bind();

		float vertices[4 * 7] = {
		   -0.3f,  0.0f,  0.0f, 	1.0f, 0.0f, 0.8f, 1.0f,
			0.3f,  0.0f,  0.0f, 	0.0f, 0.4f, 0.8f, 1.0f,
			0.0f, -0.5f,  0.0f, 	1.0f, 0.5f, 0.2f, 1.0f,
			0.0f,  0.5f,  0.0f, 	0.3f, 1.0f, 0.0f, 1.0f,
		};
		m_VertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));
		m_VertexBuffer->Bind();
		
		BufferLayout layout = {
			{ ShaderDataType::Float3, "a_Position" },
			{ ShaderDataType::Float4, "a_Color", true }
		};
		m_VertexBuffer->SetLayout(layout);

		uint32_t indices[2 * 3] = {
			0, 1, 2,
			0, 1, 3
		};
		m_IndexBuffer.reset(IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_IndexBuffer->Bind();

		m_VertexArray->AddVertexBuffer(m_VertexBuffer);
		m_VertexArray->AddIndexBuffer(m_IndexBuffer);

		std::string vertexShaderSrc = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			out vec4 v_Color;

			void main() {
				v_Color = a_Color;	
				gl_Position = vec4(a_Position, 1.0);
			}
		)";

		std::string fragmentShaderSrc = R"(
			#version 330 core

			layout(location = 0) out vec4 o_Color;

			in vec4 v_Color;

			void main() {
				o_Color = v_Color;
			}
		)";
		m_Shader.reset(new Shader(vertexShaderSrc, fragmentShaderSrc));
		m_Shader->Bind();
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

			m_VertexArray->Bind();
			glCall(glDrawElements(GL_TRIANGLES, m_IndexBuffer->GetCount(), GL_UNSIGNED_INT, 0));
			

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