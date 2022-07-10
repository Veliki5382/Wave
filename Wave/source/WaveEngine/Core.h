#pragma once

#ifdef WAVE_PLATFORM_WINDOWS

	#ifdef WAVE_EXPORT_DLL
		#define WAVE_API _declspec(dllexport)
	#else
		#define WAVE_API _declspec(dllimport)
	#endif

#else

#error Sorry, Wave Engine is currently in develop for Mac and Linux platforms!

#endif


#ifdef WAVE_PLATFORM_MAC

#endif


#ifdef WAVE_PLATFORM_LINUX

#endif


#define WAVE_BIT(x) (1 << (x))
