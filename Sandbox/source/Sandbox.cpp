#include <Wave.h>


class MainLayer : public wave::Layer {

public:
	MainLayer()
		: Layer("Main Layer") {}
	

	
	void OnUpdate() override {
		
		//WAVE_INFO("MainLayer::Event");
	}
	void OnEvent(wave::Event& e) override {
		
		WAVE_TRACE("{0}", e);
	}
};


class Sandbox : public wave::Application {

public:
	
	Sandbox() {
		PushLayer(new MainLayer);
		PushLayer(new wave::ImGuiLayer);

	}

	~Sandbox() {

	}

};

wave::Application* wave::CreateApplication() {
	
	return new Sandbox();
}
