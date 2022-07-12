#include "wavepch.h"
#include "Application.h"

#include "Events/ApplicationEvent.h"
#include "Events/MouseEvent.h"

namespace wave {

	Application::Application() {

	}
	Application::~Application() {

	}

	void Application::Run() {
		WindowResizedEvent e(6436436, 46);
		WAVE_TRACE(e);
		MouseMovedEvent vent(250, 620);
		WAVE_TRACE(vent);

		while (true);
	}

} // namespace wave