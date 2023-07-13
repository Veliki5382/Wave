#ifndef WINDOWS_WINDOW_H
#define WINDOWS_WINDOW_H

#include "WaveEngine/Core.h"
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

		inline void SetEventCallbackFunction(const EventCallbackFunction& callEvent) override { m_Data.eventCallbackFn = callEvent; }
		
		bool GetVSync() const override;
		void SetVSync(const bool status) override;
		
		void* GetNativeWindow() const override { return m_Window; }

	private:
		virtual void OnStartup(const WindowProps& props);
		virtual void Shutdown();

	private:
		GLFWwindow* m_Window;
		 
		struct WindowData {
			std::string Title = "Windows Window";
			unsigned int Width = 0, Height = 0;
			
			unsigned int m_RepeatNumber = 0;
			bool VSync = true;
			EventCallbackFunction eventCallbackFn;
		} m_Data;

	};

}



#endif