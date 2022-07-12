#ifndef LOG_H
#define LOG_H

//#include "source/wavepch.h"
#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"

namespace wave {

	class WAVE_API log {
	
	public:
		log();
		~log();

		inline static void Init();

		inline static std::shared_ptr<spdlog::logger> GetClientLog() { return s_ClientLog; }
		inline static std::shared_ptr<spdlog::logger> GetCoreLog() { return s_CoreLog; }

	private:
		static std::shared_ptr<spdlog::logger> s_ClientLog;
		static std::shared_ptr<spdlog::logger> s_CoreLog;

	};

} // namespace wave

//----Wave Core Log macros-----------------------------------------------------------

#define WAVE_CORE_TRACE(...)		wave::log::GetCoreLog()->trace(__VA_ARGS__)
#define WAVE_CORE_DEBUG(...)		wave::log::GetCoreLog()->debug(__VA_ARGS__)
#define WAVE_CORE_INFO(...)			wave::log::GetCoreLog()->info(__VA_ARGS__)
#define WAVE_CORE_WARN(...)			wave::log::GetCoreLog()->warn(__VA_ARGS__)
#define WAVE_CORE_ERROR(...)		wave::log::GetCoreLog()->error(__VA_ARGS__)
#define WAVE_CORE_FATAL(...)		wave::log::GetCoreLog()->critical(__VA_ARGS__)

//----Client Application Log macros--------------------------------------------------

#define WAVE_TRACE(...)		wave::log::GetClientLog()->trace(__VA_ARGS__)
#define WAVE_DEBUG(...)		wave::log::GetClientLog()->debug(__VA_ARGS__)
#define WAVE_INFO(...)		wave::log::GetClientLog()->info(__VA_ARGS__)
#define WAVE_WARN(...)		wave::log::GetClientLog()->warn(__VA_ARGS__)
#define WAVE_ERROR(...)		wave::log::GetClientLog()->error(__VA_ARGS__)
#define WAVE_FATAL(...)		wave::log::GetClientLog()->fatal(__VA_ARGS__)

//-----------------------------------------------------------------------------------

#endif