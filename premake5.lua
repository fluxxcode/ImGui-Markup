include "dependencies.lua"

workspace "imgui_markup"
    architecture "x86_64"
    startproject "sandbox"

    configurations
    {
        "Debug",
        "Release"
    }

    flags
    {
        "MultiProcessorCompile"
    }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

group "dependencies"
    include "imgui_markup/dependencies/imgui"
    include "sandbox/dependencies/glfw"
    include "sandbox/dependencies/glad"
group ""

include "imgui_markup"
include "sandbox"

