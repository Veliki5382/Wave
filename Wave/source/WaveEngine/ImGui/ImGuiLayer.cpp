#include "wavepch.h"
#include "ImGuiLayer.h"

#include "Platform/OpenGL/imgui_impl_opengl3.h"
#include "Platform/Windows/WindowsWindow.h"
#include "WaveEngine/Application.h"

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

		ImGui_ImplOpenGL3_Init("#version 430 core");
	}

	void ImGuiLayer::OnDettach()
	{
	}

	void ImGuiLayer::OnUpdate() {
		
		ImGuiIO& io = ImGui::GetIO();
		
		Application* app = Application::Get();
		Window* window = app->GetWindow();
		WAVE_TRACE("({0}, {1})", window->GetWidth(), window->GetHeight());
		io.DisplaySize = ImVec2(float(window->GetWidth()), float(window->GetHeight()));

		ImGui_ImplOpenGL3_NewFrame();
		ImGui::NewFrame();

		bool show = true;
		ImGui::ShowDemoWindow(&show);
		
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}
	
	void ImGuiLayer::OnEvent(Event& e)
	{
	}

} // namespace wave