#include "wavepch.h"
#include "VertexBuffer.h"
#include "WaveEngine/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLVertexBuffer.h"

#include <glad/glad.h>

namespace wave {

	VertexBuffer* VertexBuffer::Create(float* vertices, uint32_t size) {

		switch (Renderer::GetAPI()) {
			case RendererAPI::None:
				WAVE_CORE_ASSERT(false, "RendererAPI::None not supported.");
				break;

			case RendererAPI::OpenGL:
				return new OpenGLVertexBuffer(vertices, size);
				break;

			default:
				WAVE_CORE_ASSERT(false, "API not selected.");
				break;
		}
	}


} // namespace wave
