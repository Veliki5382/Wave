#include "wavepch.h"
#include "IndexBuffer.h"
#include "Renderer.h"

#include "Platform/OpenGL/OpenGLIndexBuffer.h"

namespace wave {

	IndexBuffer* IndexBuffer::Create(uint32_t* indices, uint32_t count) {
		
		switch (Renderer::GetAPI()) {
			case Renderer::API::None:
				WAVE_CORE_ASSERT(false, "RendererAPI::None not supported.");
				break;
			
			case Renderer::API::OpenGL:
				return new OpenGLIndexBuffer(indices, count);
				break;
			
			default:
				WAVE_CORE_ASSERT(false, "API not selected.");
				break;
		}
	}

}  // namespace wave