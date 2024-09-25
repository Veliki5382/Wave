#include "wavepch.h"
#include "Renderer.h"

#include "Platform/OpenGL/OpenGLRenderer.h"
#include "VertexArray.h"
#include "Shader.h"

namespace wave {

	// For now, we are only supporting OpenGL
	// TO DO: Add support for other APIs and dynamically change the API (user can choose)
	Renderer::API s_API = Renderer::API::None;
	std::unique_ptr<RendererAPI> Renderer::s_Renderer = nullptr;

	void Renderer::UseAPI(Renderer::API api) {
		
		s_API = api;
		switch (api) {
			case Renderer::API::None:
				WAVE_CORE_ASSERT(false, "RendererAPI::None not supported.");
				break;

			case Renderer::API::OpenGL:
				Renderer::s_Renderer.reset(new OpenGLRenderer());
				break;

			default:
				WAVE_CORE_ASSERT(false, "API not selected.");
				break;
		}
	}
	

	void Renderer::ClearColor(float red, float green, float blue, float alpha) {
		s_Renderer->ClearColor(red, green, blue, alpha);
	}

	void Renderer::ClearColor(const glm::vec4& color) {
		Renderer::ClearColor(color.r, color.g, color.b, color.a);
	}

	void Renderer::Begin() {
		s_Renderer->Begin();
	}

	void Renderer::End() {
		s_Renderer->End();
	}

	void Renderer::Render(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray) {
		s_Renderer->Render(shader, vertexArray);
	}

}  // namespace wave