project "ZZX"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "zzxpch.h"
	pchsource "src/zzxpch.cpp"

	files
	{
		"src/**.h",
		"src/**.cpp",
		"vendor/stb_image/**.h",
		"vendor/stb_image/**.cpp"
	}

	defines
	{
		"_CRT_SECURE_NO_WARNINGS",
		"GLFW_INCLUDE_NONE"
	}

	includedirs 
	{
		"src",
		"vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.GLAD}",
		"%{IncludeDir.Imgui}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.stb_image}",
		"%{IncludeDir.entt}",
		"%{IncludeDir.yaml_cpp}"
	}

	links
	{
		"GLFW",
		"opengl32.lib",
		"GLAD", 
		"Imgui",
		"yaml-cpp"
	}

	filter "system:windows"
		systemversion "latest"

		defines 
		{
		}
	
	filter "configurations:Debug"
		defines "ZZX_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "ZZX_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "ZZX_DIST"
		runtime "Release"
		optimize "on"
	