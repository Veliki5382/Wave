#include "wavepch.h"
#include "VertexArray.h"
#include "Renderer.h"
#include "Renderer.cpp"
#include "Platform/OpenGL/OpenGLVertexArray.h"

wave::Renderer::API wave::Renderer::s_API = wave::Renderer::API::OpenGL;

namespace wave {

    VertexArray* VertexArray::Create() {
		
		switch (Renderer::GetAPI()) {
			case Renderer::API::None:
				WAVE_CORE_ASSERT(false, "RendererAPI::None not supported.");
				break;

			case Renderer::API::OpenGL:
				return new OpenGLVertexArray();
				break;

			default:
				WAVE_CORE_ASSERT(false, "API not selected.");
				break;
		}
		return nullptr;
    }

}  // namespace wave
