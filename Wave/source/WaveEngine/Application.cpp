#include "Application.h"

#include "Events/ApplicationEvent.h"
#include "Log.h"

namespace wave {

	Application::Application() {

	}
	Application::~Application() {

	}

	void Application::Run() {
		WindowResizedEvent e(1280, 720);
		WAVE_TRACE(e);

		while (true) {}
	}

} // namespace wave