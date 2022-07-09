#include "Log.h"


namespace wave {

	std::shared_ptr<spdlog::logger> log::s_ClientLog;
	std::shared_ptr<spdlog::logger> log::s_CoreLog;

	log::log() {

	}
	log::~log() {

	}

	inline void log::Init() {
		
		spdlog::set_pattern("%^[%n][%l][%H:%M:%S:%e %p]%$ %v");

		s_ClientLog = spdlog::stdout_color_mt("USER");
		s_ClientLog->set_level(spdlog::level::trace);

		s_CoreLog = spdlog::stdout_color_mt("WAVE");
		s_CoreLog->set_level(spdlog::level::trace);
	}

} // namespace wave