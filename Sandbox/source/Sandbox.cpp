#include <Wave.h>
#include "ImGui/imgui.h"


class Layer : public wave::Layer {

public:
	Layer()
	: wave::Layer("Main Layer"), camera(-1.6f, 1.6f, 0.9f, -0.9f) {
		
		wave::Renderer::UseAPI(wave::Renderer::API::OpenGL);

		vertexArray.reset(wave::VertexArray::Create());
		vertexArray->Bind();

		float vertices[] = {
		   -0.3f,  0.0f,  0.0f, 	1.0f, 0.0f, 0.8f, 1.0f,
			0.3f,  0.0f,  0.0f, 	0.0f, 0.4f, 0.8f, 1.0f,
			0.0f, -0.5f,  0.0f, 	1.0f, 0.5f, 0.2f, 1.0f,
			0.0f,  0.5f,  0.0f, 	0.3f, 1.0f, 0.0f, 1.0f,
		};
		std::shared_ptr<wave::VertexBuffer> vertexBuffer(wave::VertexBuffer::Create(vertices, sizeof(vertices)));
		vertexBuffer->Bind();

		wave::BufferLayout layout = {
			{ wave::ShaderDataType::Float3, "a_Position" },
			{ wave::ShaderDataType::Float4, "a_Color", true }
		};
		vertexBuffer->SetLayout(layout);

		uint32_t indices[] = {
			0, 1, 2,
			0, 1, 3
		};
		std::shared_ptr<wave::IndexBuffer> indexBuffer(wave::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		indexBuffer->Bind();

		vertexArray->AddVertexBuffer(vertexBuffer);
		vertexArray->SetIndexBuffer(indexBuffer);

		// ---------------------------------------------------
		// --- Background Vertex Array setup -----------------
		// ---------------------------------------------------

		backgroundVertexArray.reset(wave::VertexArray::Create());
		backgroundVertexArray->Bind();

		float backgroundVertices[] = {
			-1.2f, -0.8f,  0.0f,
			 1.2f,  0.8f,  0.0f,
			 1.2f, -0.8f,  0.0f,
			-1.2f,  0.8f,  0.0f,
		};
		std::shared_ptr<wave::VertexBuffer> backgroundVertexBuffer(wave::VertexBuffer::Create(backgroundVertices, sizeof(backgroundVertices)));
		wave::BufferLayout backgroundLayout = {
			{ wave::ShaderDataType::Float3, "a_Position" }
		};
		backgroundVertexBuffer->SetLayout(backgroundLayout);
		backgroundVertexArray->Bind();
		backgroundVertexArray->AddVertexBuffer(backgroundVertexBuffer);

		uint32_t backgroundIndices[] = {
			0, 1, 2,
			0, 1, 3
		};

		std::shared_ptr<wave::IndexBuffer> backgroundIndexBuffer(wave::IndexBuffer::Create(backgroundIndices, sizeof(backgroundIndices) / sizeof(uint32_t)));
		backgroundIndexBuffer->Bind();
		backgroundVertexArray->SetIndexBuffer(backgroundIndexBuffer);

		std::string vertexShaderSrc = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			uniform mat4 u_VPMatrix;
			out vec4 v_Color;

			void main() {
				v_Color = a_Color;	
				gl_Position = u_VPMatrix * vec4(a_Position, 1.0);
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

			uniform mat4 u_VPMatrix;

			void main() {
				gl_Position = u_VPMatrix * vec4(a_Position, 1.0);
			}
		)";
		std::string backgroundFragmentShaderSrc = R"(
			#version 330 core

			layout(location = 0) out vec4 o_Color;

			void main() {
				o_Color = vec4(0.29f, 0.19f, 0.28f, 1.0f);
			}
		)";

		shader.reset(new wave::Shader(vertexShaderSrc, fragmentShaderSrc));
		backgroundShader.reset(new wave::Shader(backgroundVertexShaderSrc, backgroundFragmentShaderSrc));

	}
		
	void OnUpdate() override {
		
		position = camera.GetPosition();
		rotation = camera.GetRotation();

		std::cout << "Position: " << position.x << ", " << position.y << ", " << position.z << std::endl;
		// --- When compiled camera not working, things not rendering??? ---
		//WAVE_TRACE("{0}, {1}, {2}.", position.x, position.y, position.z);

		if (wave::Input::GetKeyState(WAVE_KEY_W)) {
			position.y += positionSpeed;
		}
		if (wave::Input::GetKeyState(WAVE_KEY_S)) {
			position.y -= positionSpeed;
		}
		if (wave::Input::GetKeyState(WAVE_KEY_A)) {
			position.x -= positionSpeed;
		}
		if (wave::Input::GetKeyState(WAVE_KEY_D)) {
			position.x += positionSpeed;
		}
		if (wave::Input::GetKeyState(WAVE_KEY_Q)) {
			rotation += rotationSpeed;
		}
		if (wave::Input::GetKeyState(WAVE_KEY_E)) {
			rotation -= rotationSpeed;
		}

		camera.SetPosition(position);
		camera.SetRotation(rotation);

		wave::Renderer::ClearColor(0.2f, 0.2f, 0.2f, 1.0f);

		wave::Renderer::Begin(camera);

		wave::Renderer::Render(backgroundShader, backgroundVertexArray);
		wave::Renderer::Render(shader, vertexArray);

		wave::Renderer::End();
	}

	void OnImGuiRender() override {

		ImGui::Begin("Gas");
		ImGui::Text("mame mi");
		bool ok = true;
		ImGui::Checkbox("kutija", &ok);
		ImGui::End();

	}

	void OnEvent(wave::Event& e) override {
		
		if (e.GetEventType() == wave::EventType::KeyPressed) {
			
			wave::KeyTypedEvent& event = (wave::KeyTypedEvent&)e;
			WAVE_TRACE("{0}", e);
			
			
		}
	}

private:
	wave::OrthographicCamera camera;

	glm::vec3 position;
	float positionSpeed = 0.02f;
	
	float rotation;
	float rotationSpeed = 1.0f;

	std::shared_ptr<wave::VertexArray> vertexArray, backgroundVertexArray;
	std::shared_ptr<wave::Shader> shader, backgroundShader;
};

class Sandbox : public wave::Application {

public:
	Sandbox() {
		PushLayer(new Layer());
	}

	~Sandbox() {}
};

wave::Application* wave::CreateApplication() {
	
	return new Sandbox();
}
