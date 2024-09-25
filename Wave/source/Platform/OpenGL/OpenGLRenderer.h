#ifndef OPENGL_RENDERER_H
#define OPENGL_RENDERER_H

#include "WaveEngine/Core.h"
#include "WaveEngine/Renderer/RendererAPI.h"
#include <memory>

namespace wave {


	class WAVE_API OpenGLRenderer : public RendererAPI {

	public:
		virtual void ClearColor(float red, float green, float blue, float alpha) override;
		
		virtual void Begin() override;
		virtual void End() override;

		virtual void Render(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray) override;

	};

}  // namespace wave

#endif