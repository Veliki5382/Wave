#ifndef RENDERER_API_H
#define RENDERER_API_H

#include "WaveEngine/Core.h"
#include "Shader.h"
#include "VertexArray.h"

namespace wave {

	class WAVE_API RendererAPI {

	public:
		RendererAPI() {}
		virtual ~RendererAPI() {}

		virtual void ClearColor(float red, float green, float blue, float alpha) = 0;
		
		virtual void Begin() = 0;
		virtual void End() = 0;

		virtual void Render(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray) = 0;

	};

}  // namespace wave

#endif