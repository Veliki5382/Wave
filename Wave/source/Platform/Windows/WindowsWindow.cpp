#include "wavepch.h"

#include "GLFW/glfw3.h"
#include "WindowsWindow.h"

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
			WAVE_ASSERT(done, "Could not initialize GLFW!");

			s_GLFWInitialized = true;
		}
		
		m_Window = glfwCreateWindow(m_Data.Width, m_Data.Height, m_Data.Title.c_str(), NULL, NULL);
		glfwMakeContextCurrent(m_Window);
		SetVSync(true);

	}

	void WindowsWindow::Shutdown() {
	
		glfwDestroyWindow(m_Window);
	}

	void WindowsWindow::OnUpdate() {
		glfwPollEvents();
		glfwSwapBuffers(m_Window);
	}

	bool WindowsWindow::VSyncStatus() const {
		
		return m_Data.VSync;
	}

	void WindowsWindow::SetVSync(const bool status) {

		if (status == true) {
			glfwSwapInterval(1);
			m_Data.VSync = true;
		}
		else {
			glfwSwapInterval(0);
			m_Data.VSync = false;
		}

	}

}
