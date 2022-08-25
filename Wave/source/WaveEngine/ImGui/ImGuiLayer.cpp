#include "wavepch.h"
#include "ImGuiLayer.h"

#include "Platform/OpenGL/imgui_impl_opengl3.h"
#include "Platform/Windows/WindowsWindow.h"
#include "WaveEngine/Application.h"

#include <GLAD/glad.h>

namespace wave {

	ImGuiLayer::ImGuiLayer()
		: Layer("ImGui Layer") {}

	ImGuiLayer::~ImGuiLayer()
	{
	}

	void ImGuiLayer::OnAttach() {
		
		ImGui::CreateContext();
		ImGui::StyleColorsDark();

		ImGuiIO& io = ImGui::GetIO();
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
		io.ConfigFlags |= ImGuiBackendFlags_HasSetMousePos;
		io.ConfigFlags |= ImGuiBackendFlags_HasMouseCursors;


		// ---- TEMPORARILY -> untill Wave gets its own Key Code System -----------
		io.KeyMap[ImGuiKey_Tab] = GLFW_KEY_TAB;
		io.KeyMap[ImGuiKey_LeftArrow] = GLFW_KEY_LEFT;
		io.KeyMap[ImGuiKey_RightArrow] = GLFW_KEY_RIGHT;
		io.KeyMap[ImGuiKey_UpArrow] = GLFW_KEY_UP; 
		io.KeyMap[ImGuiKey_DownArrow] = GLFW_KEY_DOWN;
		io.KeyMap[ImGuiKey_PageUp] = GLFW_KEY_PAGE_UP;
		io.KeyMap[ImGuiKey_PageDown] = GLFW_KEY_PAGE_DOWN;
		io.KeyMap[ImGuiKey_Home] = GLFW_KEY_HOME;
		io.KeyMap[ImGuiKey_End] = GLFW_KEY_END;
		io.KeyMap[ImGuiKey_Insert] = GLFW_KEY_INSERT;
		io.KeyMap[ImGuiKey_Delete] = GLFW_KEY_DELETE;
		io.KeyMap[ImGuiKey_Backspace] = GLFW_KEY_BACKSPACE;
		io.KeyMap[ImGuiKey_Space] = GLFW_KEY_SPACE;
		io.KeyMap[ImGuiKey_Enter] = GLFW_KEY_ENTER; 
		io.KeyMap[ImGuiKey_Escape] = GLFW_KEY_ESCAPE;
		io.KeyMap[ImGuiKey_A] = GLFW_KEY_A;
		io.KeyMap[ImGuiKey_C] = GLFW_KEY_C;
		io.KeyMap[ImGuiKey_V] = GLFW_KEY_V;
		io.KeyMap[ImGuiKey_X] = GLFW_KEY_X;
		io.KeyMap[ImGuiKey_Y] = GLFW_KEY_Y;
		io.KeyMap[ImGuiKey_Z] = GLFW_KEY_Z;

		ImGui_ImplOpenGL3_Init("#version 430 core");
	}

	void ImGuiLayer::OnDettach()
	{
	}

	void ImGuiLayer::OnUpdate() {
		
		ImGuiIO& io = ImGui::GetIO();
		
		Application* app = Application::Get();
		Window* window = app->GetWindow();
		//WAVE_TRACE("({0}, {1})", window->GetWidth(), window->GetHeight());
		io.DisplaySize = ImVec2(float(window->GetWidth()), float(window->GetHeight()));

		double time = glfwGetTime();
		io.DeltaTime = (time > 0.0f ? time - m_Time : 1.0f/144.0f);
		m_Time = time;

		ImGui_ImplOpenGL3_NewFrame();
		ImGui::NewFrame();

		bool show = true;
		ImGui::ShowDemoWindow(&show);
		
		glViewport(0, 0, window->GetWidth(), window->GetHeight());

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}
	
	void ImGuiLayer::OnEvent(Event& event) {
		
		EventDispatcher dispatcher(event);

		dispatcher.Dispatch<MouseButtonPressedEvent>(WAVE_BIND_FN(ImGuiLayer::OnMouseButtonPressedEvent));
		dispatcher.Dispatch<MouseButtonReleasedEvent>(WAVE_BIND_FN(ImGuiLayer::OnMouseButtonReleasedEvent));
		dispatcher.Dispatch<MouseScrolledEvent>(WAVE_BIND_FN(ImGuiLayer::OnMouseScrolledEvent));
		dispatcher.Dispatch<MouseMovedEvent>(WAVE_BIND_FN(ImGuiLayer::OnMouseMovedEvent));
		dispatcher.Dispatch<KeyTypedEvent>(WAVE_BIND_FN(ImGuiLayer::OnKeyTypedEvent));
		dispatcher.Dispatch<KeyPressedEvent>(WAVE_BIND_FN(ImGuiLayer::OnKeyPressedEvent));
		dispatcher.Dispatch<KeyReleasedEvent>(WAVE_BIND_FN(ImGuiLayer::OnKeyReleasedEvent));
		dispatcher.Dispatch<WindowResizedEvent>(WAVE_BIND_FN(ImGuiLayer::OnWindowResizedEvent));
	}

	bool ImGuiLayer::OnMouseButtonPressedEvent(MouseButtonPressedEvent& event) {
		
		ImGuiIO& io = ImGui::GetIO();
		io.MouseDown[event.GetMouseButtonCode()] = true;

		return false;
	}

	bool ImGuiLayer::OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& event) {

		ImGuiIO& io = ImGui::GetIO();
		io.MouseDown[event.GetMouseButtonCode()] = false;
		
		return false;
	}

	bool ImGuiLayer::OnMouseScrolledEvent(MouseScrolledEvent& event) {
		
		ImGuiIO& io = ImGui::GetIO();
		io.MouseWheelH = event.GetXOffset();
		io.MouseWheel = event.GetYOffset();
		
		return false;
	}

	bool ImGuiLayer::OnMouseMovedEvent(MouseMovedEvent& event) {
		
		ImGuiIO& io = ImGui::GetIO();
		io.MousePos = ImVec2(event.GetX(), event.GetY());

		return false;
	}

	bool ImGuiLayer::OnKeyTypedEvent(KeyTypedEvent& event) {

		ImGuiIO& io = ImGui::GetIO();
		


		if (event.GetKeyCode() > 0 && event.GetKeyCode() < 0x10000) {
			io.AddInputCharacter(event.GetKeyCode());
		}

		return false;
	}

	bool ImGuiLayer::OnKeyPressedEvent(KeyPressedEvent& event) {
		
		ImGuiIO& io = ImGui::GetIO();
		io.KeysDown[event.GetKeyCode()] = true;

		io.KeyCtrl = io.KeysDown[GLFW_KEY_LEFT_CONTROL] | io.KeysDown[GLFW_KEY_RIGHT_CONTROL];
		io.KeyAlt = io.KeysDown[GLFW_KEY_LEFT_ALT] | io.KeysDown[GLFW_KEY_RIGHT_ALT];
		io.KeyShift = io.KeysDown[GLFW_KEY_LEFT_SHIFT] | io.KeysDown[GLFW_KEY_RIGHT_SHIFT];
		io.KeySuper = io.KeysDown[GLFW_KEY_LEFT_SUPER] | io.KeysDown[GLFW_KEY_RIGHT_SUPER];

		return false;
	}

	bool ImGuiLayer::OnKeyReleasedEvent(KeyReleasedEvent& event) {

		ImGuiIO& io = ImGui::GetIO();
		io.KeysDown[event.GetKeyCode()] = false;
		
		return false;
	}

	bool ImGuiLayer::OnWindowResizedEvent(WindowResizedEvent& event) {
		
		ImGuiIO& io = ImGui::GetIO();
		io.DisplaySize = ImVec2(event.GetWidth(), event.GetHeight());
		io.DisplayFramebufferScale = ImVec2(1.0f, 1.0f);
		glViewport(0, 0, event.GetWidth(), event.GetHeight());

		return false;
	}


	

} // namespace wave