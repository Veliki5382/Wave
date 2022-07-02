#pragma once

#ifdef WAVE_PLATFORM_WINDOWS

extern wave::Application wave::CreateApplication();

int main(int argc, char** argv) {
	
	auto app = wave::CreateApplication();
	app.Run();

	return 0;
}

#endif

