#pragma once

#include "Core.h"
#include <iostream>

namespace wave {

	class WAVE_API Application {
	public:

		Application();
		~Application();

		void Run();

	};

	// ----- For user to define -----------
	Application CreateApplication();
}