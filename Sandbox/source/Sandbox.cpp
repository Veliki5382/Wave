#include <Wave.h>

class Sandbox : public wave::Application {
public:
	
	Sandbox() {

	}
	~Sandbox() {

	}


};

wave::Application* wave::CreateApplication() {
	
	return new Sandbox();
}
