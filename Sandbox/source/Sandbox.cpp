#include <Wave.h>
#include "ImGui/imgui.h"
#include "glm/gtc/matrix_transform.hpp"

class Layer : public wave::Layer {

public:
	Layer()
	: wave::Layer("Main Layer"), camera(-1.6f, 1.6f, 0.9f, -0.9f) {
		
		//wave::Renderer::UseAPI(wave::Renderer::API::OpenGL);

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
			-0.8f, -0.8f,  0.0f,
			 0.8f,  0.8f,  0.0f,
			 0.8f, -0.8f,  0.0f,
			-0.8f,  0.8f,  0.0f,
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
			uniform mat4 u_Transform;

			out vec4 v_Color;

			void main() {
				v_Color = a_Color;	
				gl_Position = u_VPMatrix * u_Transform * vec4(a_Position, 1.0);
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
			uniform mat4 u_Transform;

			void main() {
				gl_Position = u_VPMatrix * u_Transform * vec4(a_Position, 1.0);
			}
		)";
		std::string backgroundFragmentShaderSrc = R"(
			#version 330 core

			layout(location = 0) out vec4 o_Color;

			uniform vec4 u_Color;

			void main() {
				o_Color = u_Color;
			}
		)";

		shader.reset(wave::Shader::Create(vertexShaderSrc, fragmentShaderSrc));
		backgroundShader.reset(wave::Shader::Create(backgroundVertexShaderSrc, backgroundFragmentShaderSrc));

		for (int i = 0; i < 10; ++i) {
			for (int j = 0; j < 10; ++j) {
				transform[i][j].Scale(0.15f, 0.15f);
				transform[i][j].Translate(glm::vec3(1.8f * float(j), 1.8f * float(i), 0.0f));
			}
		}
	}
		 
	void OnUpdate(wave::Time time) override {
		
		float dt = time.GetDeltaTime();

		position = camera.GetPosition();
		rotation = camera.GetRotation();

		if (wave::Input::GetKeyState(WAVE_KEY_W)) {
			position.y += positionSpeed * dt;
		}
		if (wave::Input::GetKeyState(WAVE_KEY_S)) {
			position.y -= positionSpeed * dt;
		}
		if (wave::Input::GetKeyState(WAVE_KEY_A)) {
			position.x -= positionSpeed * dt;
		}
		if (wave::Input::GetKeyState(WAVE_KEY_D)) {
			position.x += positionSpeed * dt;
		}
		if (wave::Input::GetKeyState(WAVE_KEY_Q)) {
			rotation += rotationSpeed * dt;
		}
		if (wave::Input::GetKeyState(WAVE_KEY_E)) {
			rotation -= rotationSpeed * dt;
		}
		if (wave::Input::GetKeyState(WAVE_KEY_LEFT)) {
			playerPos.x -= positionSpeed * dt;
		}
		if (wave::Input::GetKeyState(WAVE_KEY_RIGHT)) {
			playerPos.x += positionSpeed * dt;
		}
		if (wave::Input::GetKeyState(WAVE_KEY_UP)) {
			playerPos.y += positionSpeed * dt;
		}
		if (wave::Input::GetKeyState(WAVE_KEY_DOWN)) {
			playerPos.y -= positionSpeed * dt;
		}

		camera.SetPosition(position);
		camera.SetRotation(rotation);
		
		wave::Renderer::ClearColor(0.2f, 0.2f, 0.2f, 1.0f);

		wave::Renderer::Begin(camera);

		for (int i = 0; i < 10; ++i) {
			for (int j = 0; j < 10; ++j) {
				backgroundShader->SetColor(glm::vec4(i * 0.1f, (10-j) * 0.1f, i * 0.05f + j * 0.05f, 1.0f));
				wave::Renderer::Render(backgroundShader, backgroundVertexArray, transform[i][j]);
			}
		}
		wave::Renderer::Render(shader, vertexArray, glm::translate(glm::mat4(1.0f), playerPos));

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

	wave::Transform transform[10][10];

	glm::vec3 position, playerPos = glm::vec3(0.0f);
	float positionSpeed = 1.0f;
	float rotation;
	float rotationSpeed = 50.0f;

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
