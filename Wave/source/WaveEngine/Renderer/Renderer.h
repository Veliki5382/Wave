#ifndef RENDERER_H
#define RENDERER_H

#include <glm/vec4.hpp>

#include "RendererAPI.h"
#include "VertexArray.h"
#include "Shader.h"
#include "OrthographicCamera.h"


namespace wave {

	class WAVE_API Renderer {
	
	public:
		enum class API {
			None = 0, OpenGL = 1, DirectX = 2, Vulkan = 3, Metal = 4
		};

	public:
		static void UseAPI(Renderer::API api = Renderer::API::OpenGL);
		inline static API& GetAPI() { return s_API; }

		static void ClearColor(float red, float green, float blue, float alpha);
		static void ClearColor(const glm::vec4& color);

		static void Begin(OrthographicCamera& camera);
		static void End();

		static void Render(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray);

	private:
		static API s_API;
		static std::unique_ptr<RendererAPI> s_Renderer;
	};


}  // namespace wave

#endif
