#include "wavepch.h"

#include "GLFW/glfw3.h"
#include "WindowsWindow.h"
#include "WaveEngine/Events/KeyEvent.h"
#include "WaveEngine/Events/MouseEvent.h"
#include "WaveEngine/Events/ApplicationEvent.h"

#include <GLAD/glad.h>

namespace wave {

	static bool s_GLFWInitialized = false;

	Window* Window::Create(WindowProps& props) {

		return new WindowsWindow(props);
	}

	WindowsWindow::WindowsWindow(const WindowProps& props) {

		OnStartup(props);
	}

	WindowsWindow::~WindowsWindow() {

		Shutdown();
	}

	void WindowsWindow::OnStartup(const WindowProps& props) {

		m_Data.Title = props.Title;
		m_Data.Height = props.Height;
		m_Data.Width = props.Width;
		m_Data.VSync = true;

		WAVE_CORE_INFO("Window \"{0}\" has been created, with size of ({1}, {2}).", m_Data.Title, m_Data.Width, m_Data.Height);

		if (s_GLFWInitialized == false) {

			int done = glfwInit();
			WAVE_CORE_ASSERT(done, "Could not initialize GLFW!");
			WAVE_CORE_INFO("Succesfully loaded GLFW!");

			s_GLFWInitialized = true;
		}

		m_Window = glfwCreateWindow(m_Data.Width, m_Data.Height, m_Data.Title.c_str(), NULL, NULL);
		glfwMakeContextCurrent(m_Window);

		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		WAVE_CORE_ASSERT(status, "Failed to initialize GLAD.");
		WAVE_CORE_INFO("Succesfully loaded GLAD!");

		glfwSetWindowUserPointer(m_Window, &m_Data);
		SetVSync(m_Data.VSync);
		
		glfwSetErrorCallback( [](int error, const char* description) {

			WAVE_CORE_ERROR("GLFW Error {0}: {1}", error, description);
		});


		// ------ GLFW Event Callback functions ---------------------------------------

		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height) {
			
			WindowData* data = (WindowData*)glfwGetWindowUserPointer(window);
			data->Width = width;
			data->Height = height;

			WindowResizedEvent event(width, height);
			data->eventCallbackFn(event);
		});

		glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window) {

			WindowData* data = (WindowData*)glfwGetWindowUserPointer(window);

			WindowClosedEvent event;
			data->eventCallbackFn(event);
		});
		
		glfwSetCharCallback(m_Window, [](GLFWwindow* window, unsigned int character) {

			WindowData* data = (WindowData*)glfwGetWindowUserPointer(window);

			KeyTypedEvent event(character);
			data->eventCallbackFn(event);

		});

		glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
			
			WindowData* data = (WindowData*)glfwGetWindowUserPointer(window);

			switch (action) {
				case GLFW_PRESS: {
					KeyPressedEvent event(key, 0);
					data->eventCallbackFn(event);
					break;
				}
				case GLFW_RELEASE: {
					KeyReleasedEvent event(key);
					data->eventCallbackFn(event);
					data->m_RepeatNumber = 0;
					break;
				}
				case GLFW_REPEAT: {
					KeyPressedEvent event(key, ++data->m_RepeatNumber);
					data->eventCallbackFn(event);
					break;
				}
			}

		});

		glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods) {

			WindowData* data = (WindowData*)glfwGetWindowUserPointer(window);

			switch (action) {
				case GLFW_PRESS: {
					MouseButtonPressedEvent event(button);
					data->eventCallbackFn(event);
					break;
				}
				case GLFW_RELEASE: {
					MouseButtonReleasedEvent event(button);
					data->eventCallbackFn(event);
					break;
				}
			}
			
		});

		glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xOffset, double yOffset) {

			WindowData* data = (WindowData*)glfwGetWindowUserPointer(window);

			MouseScrolledEvent event(xOffset, yOffset);
			data->eventCallbackFn(event);
		});

		glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xPos, double yPos) {

			WindowData* data = (WindowData*)glfwGetWindowUserPointer(window);

			MouseMovedEvent event(xPos, yPos);
			data->eventCallbackFn(event);
		});

	}

	void WindowsWindow::Shutdown() {

		glfwDestroyWindow(m_Window);
	}

	void WindowsWindow::OnUpdate() {
		glfwPollEvents();
		glfwSwapBuffers(m_Window);
	}

	bool WindowsWindow::GetVSync() const {

		return m_Data.VSync;
	}

	inline void WindowsWindow::SetVSync(const bool status) {

		glfwSwapInterval(status);
		m_Data.VSync = status;
	}

}
