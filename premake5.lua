include "./vendor/premake/premake_customization/solution_items.lua"

workspace "ZZX"
	architecture "x86_64"
	startproject "Editor"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

	solution_items
	{
		".editorconfig"
	}

	flags
	{
		"MultiProcessorCompile"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["GLFW"] = "%{wks.location}/ZZX/vendor/GLFW/include"
IncludeDir["GLAD"] = "%{wks.location}/ZZX/vendor/GLAD/include"
IncludeDir["Imgui"] = "%{wks.location}/ZZX/vendor/imgui"
IncludeDir["glm"] = "%{wks.location}/ZZX/vendor/glm"
IncludeDir["stb_image"] = "%{wks.location}/ZZX/vendor/stb_image"
IncludeDir["entt"] = "%{wks.location}/ZZX/vendor/entt/include"
IncludeDir["yaml_cpp"] = "%{wks.location}/ZZX/vendor/yaml-cpp/include"
IncludeDir["ImGuizmo"] = "%{wks.location}/ZZX/vendor/ImGuizmo"

group "Dependencies"
	include "vendor/premake"
	include "ZZX/vendor/GLFW"
	include "ZZX/vendor/GLAD"
	include "ZZX/vendor/imgui"
	include "ZZX/vendor/yaml-cpp"
group ""

include "ZZX"
include "Sandbox"
include "Editor"