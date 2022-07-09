#pragma once

#include "Core.h"

namespace wave {

	class WAVE_API Application {
	public:

		Application();
		virtual ~Application();

		void Run();

	};

	
	// ----- For user to define -----------
	
	Application CreateApplication();

} // namespace wave