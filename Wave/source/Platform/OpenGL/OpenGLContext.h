#ifndef OPENGL_CONTEXT_H
#define OPENGL_CONTEXT_H

#include "WaveEngine/Core.h"
#include "WaveEngine/Renderer/Context.h"

struct GLFWwindow;

namespace wave {

	class WAVE_API OpenGLContext : public Context {

	public:
		OpenGLContext(GLFWwindow* window);

		virtual void Init() override;
		virtual void SwapBuffers() override;

	private:
		GLFWwindow* m_Window;

	};


} // namespace wave

#endif
