#include "wavepch.h"

#include "OpenGLContext.h"
#include <GLFW/glfw3.h>
#include <GLAD/glad.h>

namespace wave {


	OpenGLContext::OpenGLContext(GLFWwindow* window)
	  : m_Window(window) {
		WAVE_CORE_ASSERT(window != nullptr, "Window cannot be null-pointer!")
	}
	
	void OpenGLContext::Init() {

		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		WAVE_CORE_ASSERT(status, "Failed to initialize GLAD.");
		WAVE_CORE_INFO("Succesfully loaded GLAD!");
	}

	void wave::OpenGLContext::SwapBuffers() {

		glfwSwapBuffers(m_Window);
	}


} // namespace wave