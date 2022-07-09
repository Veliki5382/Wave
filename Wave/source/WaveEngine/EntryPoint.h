#pragma once

#ifdef WAVE_PLATFORM_WINDOWS

//extern wave::Application wave::CreateApplication();

int main(int argc, char** argv) {
	
	wave::log::Init();
	
	WAVE_CORE_INFO("Welcome to Wave Engine!");
	WAVE_INFO("Succesfully started application. Congrats!");
	WAVE_CORE_WARN("Be careful...");
	WAVE_CORE_ERROR("You've run into an error.");

	auto app = wave::CreateApplication();
	app.Run();

	return 0;
}

#endif

