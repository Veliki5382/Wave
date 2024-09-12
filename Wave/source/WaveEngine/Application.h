#ifndef APPLICATION_H
#define APPLICATION_H

//#include "source/wavepch.h"
#include "Core.h"
#include "LayerStack.h"
#include "Platform/Windows/WindowsWindow.h"
#include "Events/ApplicationEvent.h"
#include "ImGui/ImGuiLayer.h"
#include "Renderer/VertexBuffer.h"
#include "Renderer/IndexBuffer.h"
#include "Renderer/Shader.h"

namespace wave {

	class WAVE_API Application {
	public:

		Application();
		virtual ~Application();

		void Run();
		void onEvent(Event& e);

		void PushLayer(Layer* layer);

		inline Window& GetWindow() { return *m_Window; }
		inline static Application& Get() { return *s_Instance; }

	private:
		bool windowClosed(WindowClosedEvent& e);
		
		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running;
		LayerStack m_LayerStack;

		unsigned int m_VertexArray;
		std::unique_ptr<VertexBuffer> m_VertexBuffer;
		std::unique_ptr<IndexBuffer> m_IndexBuffer;
		std::unique_ptr<Shader> m_Shader;
	
	private:
		static Application* s_Instance;
	};

	
	// ----- For user to define -----------
	
	Application* CreateApplication();

} // namespace wave

#endif