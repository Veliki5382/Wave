#ifndef WINDOWS_WINDOW_H
#define WINDOWS_WINDOW_H

#include "WaveEngine/Window.h"

#include "GLFW/include/GLFW/glfw3.h"

namespace wave {


	class WAVE_API WindowsWindow : public Window{

	public:
		WindowsWindow(const WindowProps& props);
		virtual ~WindowsWindow();

		void OnUpdate() override;

		inline unsigned int GetWidth() const override { return m_Data.Width; }
		inline unsigned int GetHeight() const override { return m_Data.Height; }

		bool VSyncStatus() const override;
		void SetVSync(const bool status) override;
		
	private:
		virtual void OnStartup(const WindowProps& props);
		virtual void Shutdown();

	private:
		GLFWwindow* m_Window;
		
		struct WindowData {
			std::string Title;
			unsigned int Width, Height;
			bool VSync;
		};
		
		WindowData m_Data;

	};

}



#endif