#include "wavepch.h"
#include "VertexArray.h"

#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace wave {

    VertexArray* VertexArray::Create() {
		
		switch (Renderer::GetAPI()) {
		case RendererAPI::None:
			WAVE_CORE_ASSERT(false, "RendererAPI::None not supported.");
			break;

		case RendererAPI::OpenGL:
			return new OpenGLVertexArray();
			break;

		default:
			WAVE_CORE_ASSERT(false, "API not selected.");
			break;
		}
		return nullptr;
    }

}  // namespace wave
