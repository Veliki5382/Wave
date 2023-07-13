workspace "Wave"
	
	architecture "x64"
	startproject "Sandbox"

	configurations {
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.system}-%{cfg.buildcfg}-%{cfg.architecture}"


--  include Dirs relative to $(SolutionDir)
IncludeDir = {}
IncludeDir["GLFW"] = "Wave/include/GLFW/include/"
IncludeDir["GLAD"] = "Wave/include/GlAD/include/"
IncludeDir["ImGui"] = "Wave/include/ImGui/"
IncludeDir["glm"] = "Wave/include/glm/"


group "Dependencies"
	include "Wave/include/GLFW/premake5.lua"
	include "Wave/include/GLAD/premake5.lua"
	include "Wave/include/ImGui/premake5.lua"
group ""


--- PROJECT WAVE ---------------------------------------------------

project "Wave"
	location "Wave"
	kind "StaticLib"
	staticruntime "on"
	language "C++"
	cppdialect "C++17"
	systemversion "latest"


	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	
	pchheader "wavepch.h"
	pchsource "Wave/source/wavepch.cpp"

	files {
		"%{prj.name}/source/**.h",
		"%{prj.name}/source/**.cpp",
		"%{prj.name}/source/Platform/Windows/**.h",
		"%{prj.name}/source/Platform/Windows/**.cpp",
		"%{prj.name}/source/WaveEngine/**.h",	
		"%{prj.name}/source/WaveEngine/**.cpp",
		"%{prj.name}/source/WaveEngine/Events/**.h",
		"%{prj.name}/source/WaveEngine/ImGui/**.h",
		"%{prj.name}/source/WaveEngine/ImGui/**.h"
	}

	includedirs {
		"%{prj.name}/",
		"%{prj.name}/source/",
		"%{prj.name}/include/",
		"%{IncludeDir.GLFW}/",
		"%{IncludeDir.GLAD}/",
		"%{IncludeDir.ImGui}/",
		"%{IncludeDir.glm}/"
	}

	links {
		"GLFW",
		"GLAD",
		"ImGui",
		"opengl32.lib"
	}

	
	--- FILTERS --------------------------------------

	filter "system:windows"
		
		defines {
			"WAVE_PLATFORM_WINDOWS",
			"WAVE_LINK_STATIC",
			"WAVE_EXPORT_DLL",
			"WAVE_INCLUDE_OPENGL"
		}

	filter "system:mac"
		
		defines {
			"WAVE_PLATFORM_MAC"
		}

	filter "system:linux"
		
		defines {
			"WAVE_PLATFORM_LINUX"
		}
	
	--- CONFIGURATIONS -------------------------------

	filter "configurations:Debug"
		defines {
			"WAVE_MODE_DEBUG",
			"WAVE_ASSERT_ENABLED"
		}
		symbols "on"

	filter "configurations:Release"
		defines {
			"WAVE_MODE_RELEASE"
		}
		optimize "on"

	filter "configurations:Dist"
		defines {
			"WAVE_MODE_DIST"
		}
		optimize "on"

--- PROJECT SANDBOX ------------------------------------------------

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	staticruntime "on"
	language "C++"
	cppdialect "C++17"
	systemversion "latest"

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
		"Wave/include/",
		"Wave/include/GLFW/include/",
		"%{IncludeDir.glm}/"
	}

	links {
		"Wave"
	}


	--- FILTERS --------------------------------------

	filter "system:windows"

		defines {
			"WAVE_PLATFORM_WINDOWS"
		}

	filter "system:mac"
		
		defines {
			"WAVE_PLATFORM_MAC"
		}

	filter "system:linux"
		
		defines {
			"WAVE_PLATFORM_LINUX"
		}
	

	filter "configurations:Debug"
		defines {
			"WAVE_MODE_DEBUG"
		}
		symbols "on"

	filter "configurations:Release"
		defines {
			"WAVE_MODE_RELEASE"
		}
		optimize "on"

	filter "configurations:Dist"
		defines {
			"WAVE_MODE_DIST"
		}
		optimize "on"

--------------------------------------------------------------------