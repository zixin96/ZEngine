project "ZZX"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	-- Link run time library statically
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
		"vendor/stb_image/**.cpp",
		"vendor/ImGuizmo/ImGuizmo.h",
		"vendor/ImGuizmo/ImGuizmo.cpp"
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
		"%{IncludeDir.yaml_cpp}",
		"%{IncludeDir.ImGuizmo}"
	}

	links
	{
		"GLFW",
		"opengl32.lib",
		"GLAD", 
		"Imgui",
		"yaml-cpp"
	}

	filter "files:vendor/ImGuizmo/**.cpp"
	flags { "NoPCH" }

	filter "system:windows"
		systemversion "latest"

		defines 
		{
		}
	
	filter "configurations:Debug"
		defines "ZE_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "ZE_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "ZE_DIST"
		runtime "Release"
		optimize "on"
	