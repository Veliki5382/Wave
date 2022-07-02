#pragma once

#ifdef WAVE_PLATFORM_WINDOWS

#ifdef WAVE_BUILD_DLL
	#define WAVE_API _declspec(dllexport)
#else
	#define WAVE_API _declspec(dllimport)
#endif

#else

#error Sorry, Wave Engine is still for Windows only! 

#endif