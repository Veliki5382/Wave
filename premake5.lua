workspace "Wave"
	
	architecture "x64"
	configurations {
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.system}-%{cfg.buildcfg}-%{cfg.architecture}"


--- PROJECT WAVE ---------------------------------------------------

project "Wave"
	location "Wave"
	kind "SharedLib"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files {
		"%{prj.name}/source/Wave.h",
		"%{prj.name}/source/WaveEngine/**.h",	
		"%{prj.name}/source/WaveEngine/**.cpp",
		"%{prj.name}/source/WaveEngine/Events/**.h"
	}

	includedirs {
		"%{prj.name}/",
		"%{prj.name}/source/",
		"%{prj.name}/include/"
	}
	
	--- FILTERS --------------------------------------

	filter "system:windows"
		cppdialect "C++17	"
		staticruntime "On"
		systemversion "10.0"

		defines {
			"WAVE_PLATFORM_WINDOWS",
			"WAVE_EXPORT_DLL"
		}

		postbuildcommands {
			("{COPYFILE} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox/")
		}

	filter "system:mac"
		staticruntime "On"
		systemversion "latest"

		defines {
			"WAVE_PLATFORM_MAC"
		}

	filter "system:linux"
		staticruntime "On"
		systemversion "latest"

		defines {
			"WAVE_PLATFORM_LINUX"
		}
	
	--- CONFIGURATIONS -------------------------------

	filter "configurations:Debug"
		defines {
			"WAVE_DEBUG"
		}
		symbols "On"

	filter "configurations:Release"
		defines {
			"WAVE_RELEASE"
		}
		optimize "On"

	filter "configurations:Dist"
		defines {
			"WAVE_DIST"
		}
		optimize "On"

--- PROJECT SANDBOX ------------------------------------------------

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"

	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files {
		"%{prj.name}/source/**.h",	
		"%{prj.name}/source/**.cpp"
	}

	includedirs {
		"%{prj.name}/",
		"%{prj.name}/source/",
		"Wave/source/",
		"Wave/include/"
	}

	links {
		"Wave"
	}


	--- FILTERS --------------------------------------

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "10.0"

		defines {
			"WAVE_PLATFORM_WINDOWS"
		}

	filter "system:mac"
		staticruntime "On"
		systemversion "latest"

		defines {
			"WAVE_PLATFORM_MAC"
		}

	filter "system:linux"
		staticruntime "On"
		systemversion "latest"

		defines {
			"WAVE_PLATFORM_LINUX"
		}
	

	filter "configurations:Debug"
		defines {
			"WAVE_DEBUG"
		}
		symbols "On"

	filter "configurations:Release"
		defines {
			"WAVE_RELEASE"
		}
		optimize "On"

	filter "configurations:Dist"
		defines {
			"WAVE_DIST"
		}
		optimize "On"

--------------------------------------------------------------------