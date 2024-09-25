#include "wavepch.h"
#include "Application.h"
#include "Renderer/Renderer.h"


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


		Renderer::UseAPI(Renderer::API::OpenGL);

		// ---------------------------------------------------
		// --- Main Vertex Array setup -----------------------
		// ---------------------------------------------------


		m_VertexArray.reset(VertexArray::Create());
		m_VertexArray->Bind();

		float vertices[] = {
		   -0.3f,  0.0f,  0.0f, 	1.0f, 0.0f, 0.8f, 1.0f,
			0.3f,  0.0f,  0.0f, 	0.0f, 0.4f, 0.8f, 1.0f,
			0.0f, -0.5f,  0.0f, 	1.0f, 0.5f, 0.2f, 1.0f,
			0.0f,  0.5f,  0.0f, 	0.3f, 1.0f, 0.0f, 1.0f,
		};
		std::shared_ptr<VertexBuffer> vertexBuffer(VertexBuffer::Create(vertices, sizeof(vertices)));
		vertexBuffer->Bind();
		
		BufferLayout layout = {
			{ ShaderDataType::Float3, "a_Position" },
			{ ShaderDataType::Float4, "a_Color", true }
		};
		vertexBuffer->SetLayout(layout);

		uint32_t indices[] = {
			0, 1, 2,
			0, 1, 3
		};
		std::shared_ptr<IndexBuffer> indexBuffer(IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		indexBuffer->Bind();

		m_VertexArray->AddVertexBuffer(vertexBuffer);
		m_VertexArray->SetIndexBuffer(indexBuffer);

		// ---------------------------------------------------
		// --- Background Vertex Array setup -----------------
		// ---------------------------------------------------

		m_BackgroundVertexArray.reset(VertexArray::Create());
		m_BackgroundVertexArray->Bind();

		float backgroundVertices[] = {
			-0.8f, -0.9f,  0.0f,
			 0.8f,  0.7f,  0.0f,
			 0.8f, -0.9f,  0.0f,
			-0.8f,  0.7f,  0.0f,
		};
		std::shared_ptr<VertexBuffer> backgroundVertexBuffer(VertexBuffer::Create(backgroundVertices, sizeof(backgroundVertices)));
		BufferLayout backgroundLayout = {
			{ ShaderDataType::Float3, "a_Position" }
		};
		backgroundVertexBuffer->SetLayout(backgroundLayout);
		m_BackgroundVertexArray->Bind();
		m_BackgroundVertexArray->AddVertexBuffer(backgroundVertexBuffer);

		uint32_t backgroundIndices[] = {
			0, 1, 2,
			0, 1, 3
		};

		std::shared_ptr<IndexBuffer> backgroundIndexBuffer(IndexBuffer::Create(backgroundIndices, sizeof(backgroundIndices) / sizeof(uint32_t)));
		backgroundIndexBuffer->Bind();
		m_BackgroundVertexArray->SetIndexBuffer(backgroundIndexBuffer);

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

		std::string backgroundVertexShaderSrc = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;

			void main() {
				gl_Position = vec4(a_Position, 1.0);
			}
		)";
		std::string backgroundFragmentShaderSrc = R"(
			#version 330 core

			layout(location = 0) out vec4 o_Color;

			void main() {
				o_Color = vec4(0.29f, 0.19f, 0.28f, 1.0f);
			}
		)";

		m_Shader.reset(new Shader(vertexShaderSrc, fragmentShaderSrc));
		m_BackgroundShader.reset(new Shader(backgroundVertexShaderSrc, backgroundFragmentShaderSrc));

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
			
			Renderer::ClearColor(0.2f, 0.2f, 0.2f, 1.0f);
			
			Renderer::Begin();

			Renderer::Render(m_BackgroundShader, m_BackgroundVertexArray);
			Renderer::Render(m_Shader, m_VertexArray);

			Renderer::End();

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