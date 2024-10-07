#ifndef OPENGL_RENDERER_H
#define OPENGL_RENDERER_H

#include "WaveEngine/Core.h"
#include "WaveEngine/Renderer/RendererAPI.h"
#include "WaveEngine/Renderer/OrthographicCamera.h"
#include "WaveEngine/Renderer/Transform.h"

namespace wave {


	class WAVE_API OpenGLRenderer : public RendererAPI {

	public:
		OpenGLRenderer();

		virtual void ClearColor(float red, float green, float blue, float alpha) override;
		
		virtual void Begin(OrthographicCamera& camera) override;
		virtual void End() override;

		virtual void Render(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray, const Transform& transform) override;

	private:
		glm::mat4& m_VPMatrix;
	};


}  // namespace wave

#endif