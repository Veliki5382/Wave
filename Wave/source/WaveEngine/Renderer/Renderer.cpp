#include "wavepch.h"
#include "Renderer.h"

namespace wave {

	// For now, we are only supporting OpenGL
	// TO DO: Add support for other APIs and dynamically change the API (user can choose)
	RendererAPI Renderer::s_RendererAPI = RendererAPI::OpenGL;

} // namespace wave