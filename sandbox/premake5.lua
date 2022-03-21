--sandbox

project "sandbox"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"
    staticruntime "off"

    targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
    objdir ("%{wks.location}/obj/" .. outputdir .. "/%{prj.name}")

    pchheader "sapch.h"
    pchsource "src/sapch.cpp"

    files
    {
        "src/**.h",
        "src/**.cpp",

        "%{include_dir.imgui}/backends/imgui_impl_opengl3.h",
        "%{include_dir.imgui}/backends/imgui_impl_opengl3.cpp",
        "%{include_dir.imgui}/backends/imgui_impl_glfw.h",
        "%{include_dir.imgui}/backends/imgui_impl_glfw.cpp",
    }

    includedirs
    {
        "%{wks.location}/sandbox/src",
        "%{include_dir.imgui_markup}",
        "%{include_dir.imgui}",
        "%{include_dir.glfw}",
        "%{include_dir.glad}"
    }

    links
    {
        "imgui_markup",
        "imgui",
        "glfw",
        "glad"
    }

    filter "files:**/backends/**.cpp"
        flags { "NoPCH" }

    filter "system:windows"
        systemversion "latest"
        defines "_PLATFORM_WINDOWS"
        links
        {
            "opengl32.lib"
        }

    filter "system:linux"
        systemversion "latest"
        defines "_PLATFORM_LINUX"
        links
        {
            "GL",
            "GLU",
            "glut",
            "dl",
            "pthread"
        }

    filter "configurations:Debug"
        symbols "on"

    filter "configurations:Release"
        optimize "on"
