project "Editor"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"src/**.h",
		"src/**.cpp"
	}

	includedirs
	{
		"%{wks.location}/ZZX/vendor/spdlog/include",
		"%{wks.location}/ZZX/src",
		"%{wks.location}/ZZX/vendor",
		"%{IncludeDir.glm}",
		"%{IncludeDir.entt}",
		"%{IncludeDir.ImGuizmo}"
	}

	links
	{
		"ZZX"
	}

	filter "system:windows"
		systemversion "latest"

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
