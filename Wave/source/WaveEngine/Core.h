#ifndef CORE_H
#define CORE_H

#ifdef WAVE_PLATFORM_WINDOWS
	#ifdef WAVE_LINK_DYNAMIC
		#ifdef WAVE_EXPORT_DLL
			#define WAVE_API _declspec(dllexport)
		#else
			#define WAVE_API _declspec(dllimport)
		#endif
	#else
		#define WAVE_API 
	#endif
#else
	#error Sorry, Wave Engine is currently in develop for Mac and Linux platforms!
#endif

#ifdef WAVE_PLATFORM_MAC

#endif

#ifdef WAVE_PLATFORM_LINUX

#endif

// --- DEBUG FEATURES ------------------------------------------------------

#define WAVE_BIT(x) (1 << (x))

#ifdef WAVE_ASSERT_ENABLED
	#define WAVE_ASSERT(x, ...) { if(x == false) {WAVE_ERROR("Assertion failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define WAVE_CORE_ASSERT(x, ...) { if(x == false) {WAVE_CORE_ERROR("Assertion failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define WAVE_ASSERT(x, ...)
	#define WAVE_CORE_ASSERT(x, ...)
#endif

#define WAVE_BIND_FN(fn) std::bind(&fn, this, std::placeholders::_1)


#endif // CORE_H