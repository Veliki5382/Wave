#ifndef ENTRY_POINT_H
#define ENTRY_POINT_H

//#include "source/wavepch.h"

#ifdef WAVE_PLATFORM_WINDOWS

//extern wave::Application* wave::CreateApplication();

int main(int argc, char** argv) {
	
	wave::log::Init();
	
	WAVE_INFO("Welcome to Wave Engine!");

	wave::Application* app = wave::CreateApplication();
	app->Run();
	delete app;

	return 0;
}

#endif // WAVE_PLATFORM_WINDOWS

#endif