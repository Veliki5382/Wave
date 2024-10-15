#include "wavepch.h"
#include "Shader.h"

#include "Platform/OpenGL/OpenGLShader.h"
#include "Renderer.h"

namespace wave {

	Shader* Shader::Create(std::string& vertexSrc, std::string& fragmentSrc) {

		switch (Renderer::GetAPI()) {
			
			case Renderer::API::None:
				WAVE_CORE_ASSERT(false, "API::None not supported.");
				break;
			case Renderer::API::OpenGL:
				return new OpenGLShader(vertexSrc, fragmentSrc);
				break;
			default:
				WAVE_CORE_ASSERT(false, "API not selected.");
				break;
		}
		
	}

}  // namespace wave